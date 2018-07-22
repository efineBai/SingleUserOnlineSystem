
var PROTO_PATH =  __dirname + "/../protos/single_user_online.proto";
var grpc = require('grpc');
var protoLoader = require('@grpc/proto-loader');
// Suggested options for similarity to existing grpc.load behavior
var packageDefinition = protoLoader.loadSync(
    PROTO_PATH,
    {keepCase: true,
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
function SignUp(call, callback){
    var resultInfo = new messages.ResultInfo();
    resultInfo.setResultcode(0);
    resultInfo.setResultmsg("SignSuccess");
    callback(null, resultInfo);

}

function Logout(call, callback){

}

function KeepAliveStream(call){

}

function KeepAliveShort(call, callback){

}

function getServer() {
    var server = new grpc.Server();
    server.addService(services.SingleUserOnlineService, {
        signUp: SignUp,
        logout: Logout,
        keepAliveStream: KeepAliveStream,
        keepAliveShort: KeepAliveShort

    });
    return server;
}
var routeServer = getServer();
routeServer.bind('0.0.0.0:50051', grpc.ServerCredentials.createInsecure());
routeServer.start();
console.log("hello grpc")