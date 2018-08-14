var PROTO_PATH = __dirname + "/../protos/single_user_online.proto";
var grpc = require('grpc');
var protoLoader = require('@grpc/proto-loader');
var globalConf = require('./GlobalConf');
const crypto = require('crypto');
// Suggested options for similarity to existing grpc.load behavior
var packageDefinition = protoLoader.loadSync(
    PROTO_PATH,
    {
        keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true
    });
var protoDescriptor = grpc.loadPackageDefinition(packageDefinition);
// The protoDescriptor object has the full package hierarchy
var singleUserOnline = protoDescriptor.SingleUserOnline;

var Server = new grpc.Server();

/**
 * implements SingleUserOnline Interfaces
 */
// proto 生成的js
var messages = require('./single_user_online_pb');
var services = require('./single_user_online_grpc_pb');
// 数据库操作
var db = require('./DBOperations');
//先创建user_info表
db.createTables(function (result) {
    console.log("createtables result is " + result);
});
var commTools = require('./CommTools');
// SignUp
function signUp(call, callback) {
    var loginInfo = call.request;
    console.log("sign up called,"+ loginInfo.getUserid()+"; pwd="+ loginInfo.getPasswordencoded());
    var resultInfo = new messages.ResultInfo();
    var passwd = commTools.RsaDecode(loginInfo.getPasswordencoded());
    if(passwd != null && passwd.length <= 10) {
        // 返回失败
        resultInfo.setResultcode(global.USER_INFO_ILLEGAL);
        resultInfo.setResultmsg("pwd is empty or length is less than 10");
        callback(null, resultInfo);
        return;
    }
    passwd = passwd.substr(0, passwd.length -10);
    loginInfo.setPasswordencoded(passwd);

    db.createNewUser(loginInfo.getUserid(), loginInfo.getPasswordencoded(), function (resultCode) {
        if (resultCode === 0) {
            resultInfo.setResultcode(global.USER_SIGNUP_SUCC);
            resultInfo.setResultmsg("sign up success");
        } else {
            resultInfo.setResultcode(global.USER_SIGNUP_ERR);
            resultInfo.setResultmsg("sign up failed");
        }
        callback(null, resultInfo)
    });

}

function logout(call, callback) {
    console.log("log out called");
    var resultInfo = new messages.ResultInfo();
    var loginInfo = call.request;
    var lastCallInfo = global.allUserCall.get(loginInfo.getUserid());
    if (lastCallInfo !== undefined) {
        if (lastCallInfo.getDeviceid() == call.getDeviceid()) {
            // 登出请求成功
            resultInfo.setResultcode(global.USER_LOGOUT_SUCC);
            call.write(resultInfo);
            lastCallInfo.end();
        }
    }
}

function keepAliveStream(call) {

    call.on('data', function (loginInfo) {
        console.log("keepAliveStream called");
        db.queryPwd(loginInfo.getUserid(), function (pwd) {
            if (pwd !== null && pwd.length!==0) {
                var time_stamp = loginInfo.getTimestamp();
                const hash = crypto.createHash('md5');
                hash.update(pwd + time_stamp);
                var hash_ret = hash.digest('hex');
                if (hash_ret.toLowerCase() ==loginInfo.getPasswordencoded().toLowerCase()) {

                    //密码匹配成功,需要先看之前是否已经有连接了
                    var lastUserStatus = global.allUserCall.get(loginInfo.getUserid());
                    if(lastUserStatus == null && global.allcheckingUser.has(loginInfo.getUserid())) {
                        lastUserStatus = global.allcheckingUser.get(loginInfo.getUserid());
                    }

                    if (lastUserStatus != undefined) {
                        // 之前的连接已经存在，查看status
                        var lastLoginInfo = lastUserStatus.loginInfo;

                        switch (loginInfo.getStatus()) {

                            case global.CLIENT_USER_LOGIN:
                                console.log("old user " + lastLoginInfo.getUserid() + " start to connect");
                                lastLoginInfo.setStatus(global.USER_LOGIN_OTHER)
                                lastUserStatus.call.write(lastLoginInfo);
                                lastUserStatus.call.end();
                                global.allUserCall.set(loginInfo.getUserid(), new globalConf.CallStatus(call, loginInfo, "keepAliveStream"));
                                global.allcheckingUser.delete(loginInfo.getUserid());
                                loginInfo.setStatus(global.USER_LOGIN_SUCC);
                                call.write(loginInfo)
                                break;

                            case global.CLIENT_USER_LOGOUT:
                                console.log("user " + lastLoginInfo.getUserid() + " star to logOUT");
                                lastUserStatus.call.end();
                                break;
                            // 用户响应svr的 检测alive请求
                            case global.CLIENT_KEEP_ALIVE:
                                global.allUserCall.set(loginInfo.getUserid(), global.allcheckingUser.get(loginInfo.getUserid()));
                                global.allcheckingUser.delete(loginInfo.getUserid());
                                loginInfo.setStatus(global.USER_LOGIN_SUCC);
                                call.write(loginInfo)
                                break;

                            default:
                                // 先默认为登录
                                console.log("old user " + lastLoginInfo.getUserid() + " start to connect");
                                lastLoginInfo.setStatus(global.USER_LOGIN_OTHER)
                                lastUserStatus.call.write(lastLoginInfo);
                                lastUserStatus.call.end();
                                global.allUserCall.set(loginInfo.getUserid(), new globalConf.CallStatus(call, loginInfo, "keepAliveStream"));
                                global.allcheckingUser.delete(loginInfo.getUserid());
                                loginInfo.setStatus(global.USER_LOGIN_SUCC);
                                call.write(loginInfo)
                        }

                    } else {
                        // 之前该用户并没有在线
                        console.log("new user " + loginInfo.getUserid() + " start to connect");
                        global.allUserCall.set(loginInfo.getUserid(), call);
                        loginInfo.setStatus(global.USER_LOGIN_SUCC);
                        call.write(loginInfo);
                        global.allUserCall.set(loginInfo.getUserid(), new globalConf.CallStatus(call, loginInfo, "keepAliveStream"));

                    }

                    // 为新的一次登录建立连接

                } else {

                    loginInfo.setStatus(global.USER_PWD_ERROR);
                    call.write(loginInfo);
                }
            } else {
                loginInfo.setStatus(global.USER_NOT_EXIST);
                call.write(loginInfo);

            }
        });

    });
    call.on('end', function (loginInfo) {
        console.log( "end: break connection");
        call.end();
    });

    call.on('error', function (loginInfo) {
        console.error("ERROR: user:  break connection");
       call.error();
    })

}

//暂时先不做，用于低频率的keep-alive请求
function keepAliveShort(call, callback) {

}

function getServer() {
    var server = new grpc.Server();
    server.addService(services.SingleUserOnlineService, {
        signUp: signUp,
        logout: logout,
        keepAliveStream: keepAliveStream,
        keepAliveShort: keepAliveShort
    });
    return server;
}

var schedule = require('node-schedule');

// 每一分钟遍历一次所有已经连接的用户，
function checkUserLoged(){
    schedule.scheduleJob("30 * * * * *", function () {
        for(var  callstatus in global.allUserCall) {
            var loginInfo  = callstatus.loginInfo;
            loginInfo.setStatus(global.USER_STATUS_CHECK_SUCC);
            global.allcheckingUser.set(loginInfo.getUserid(), callstatus);
            global.allUserCall.delete(loginInfo.getUserid());
        }
    })
}

// 按照一定的规则将用户进行剔除
function kickoutTargetUsers(){
    schedule.scheduleJob("1 * * * * *", function () {
        db.loadRules(function (array) {
            if(array.length == 0){
                // 不需要剔除用户
                return;
            } else{
                global.allUserCall.forEach(function (status, username, map) {
                    array.forEach(function (rexp, index, array) {
                        if (username.match(rexp)){
                            console.log("user %s match", username);
                            var lastloginInfo = status.loginInfo;
                            lastloginInfo.setStatus(global.USER_LOGIN_OTHER)
                            status.call.write(lastloginInfo);
                            status.call.end();
                        }
                    });
                });
            }
        });
    });

}

var routeServer = getServer();
routeServer.bind('0.0.0.0:3001', grpc.ServerCredentials.createInsecure());
routeServer.start();
// checkUserLoged();
kickoutTargetUsers();
console.log("hello grpc")