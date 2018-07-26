var PROTO_PATH = __dirname + "/../protos/single_user_online.proto";
var grpc = require('grpc');
var protoLoader = require('@grpc/proto-loader');
var globalConf = require('./GlobalConf');
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

// SignUp
function signUp(call, callback) {
    var loginInfo = call.request;
    var resultInfo = new messages.ResultInfo();
    db.createNewUser(loginInfo.getUserid(), loginInfo.getPasswordencoded(), function (resultCode) {
        if (resultCode === 0) {
            resultInfo.setResultcode(0);
            resultInfo.setResultmsg("sign up success");
        } else {
            resultInfo.setResultcode(-1);
            resultInfo.setResultmsg("sign up failed");
        }
        callback(null, resultInfo)
    });

}

function logout(call, callback) {
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
        console.log(typeof (loginInfo));

        db.queryPwd(loginInfo.getUserid(), function (pwd) {

            if (pwd !== undefined && pwd.length > 0) {

                if (loginInfo.getPasswordencoded() == pwd) {
                    //密码匹配成功,需要先看之前是否已经有连接了
                    var lastUserStatus = global.allUserCall.get(loginInfo.getUserid());

                    if (lastUserStatus != undefined) {
                        // 之前的连接已经存在，查看status
                        var lastLoginInfo = lastUserStatus.loginInfo;

                        switch(lastLoginInfo.getStatus()){

                            case global.CLIENT_USER_LOGIN:
                                console.log("old user " + lastLoginInfo.getUserid() + " start to connect");
                                lastLoginInfo.setStatus(global.USER_LOGIN_OTHER)
                                lastUserStatus.call.write(lastLoginInfo);
                                lastUserStatus.call.end();
                                break;

                            case global.CLIENT_USER_LOGOUT:
                                console.log("user "+ lastLoginInfo.getUserid() + " star to logOUT");
                                lastUserStatus.call.end();
                                break;

                            case defaultStatus:
                                // 先默认为登录
                                console.log("default: old user " + lastLoginInfo.getUserid() + " start to connect");
                                lastLoginInfo.setStatus(global.USER_LOGIN_OTHER)
                                lastUserStatus.call.write(lastLoginInfo);
                                lastUserStatus.call.end();
                        }

                    } else {
                        console.log("new user " + loginInfo.getUserid() + " start to connect");
                    }

                    // 为新的一次登录建立连接
                    global.allUserCall.set(loginInfo.getUserid(), new globalConf.CallStatus(call, loginInfo, "keepAliveStream"));
                    loginInfo.setStatus(global.USER_LOGIN_SUCC);
                    call.write(loginInfo)
                } else {

                    loginInfo.setStatus(global.USER_PWD_ERROR);
                    call.write(loginInfo);
                }
            } else {
                loginInfo.setResultcode(global.USER_NOT_EXIST);
                call.write(loginInfo);
            }
        });
    });
    call.on('end', function (loginInfo) {
        console.log("user: "+ loginInfo.getUserid() +" break connection");
        global.allUserCall.delete(loginInfo.getUserid());
    });

    call.on('error', function (loginInfo) {
        console.error("ERROR: user: "+ loginInfo.getUserid() +" break connection");
        global.allUserCall.delete(loginInfo.getUserid());
    })

}

//
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

var routeServer = getServer();
routeServer.bind('0.0.0.0:50051', grpc.ServerCredentials.createInsecure());
routeServer.start();
console.log("hello grpc")