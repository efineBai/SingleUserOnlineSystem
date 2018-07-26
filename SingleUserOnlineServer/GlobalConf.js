// global.RSA_PUB_KEY = ;
// global.RSA_PRI_KEY = ;
global.allUserCall = new Map();

function CallStatus(call, loginInfo, functionName){
    this.call = call;
    this.loginInfo = loginInfo;
    this.functionName = functionName;
    this.createTime = Date.now();
    this.lastActiveTime = Date.now();
    this.deviceid = loginInfo.getDeviceid();
}

// 服务端返回的错误码
global.USER_PWD_ERROR = -10001;
global.USER_NOT_EXIST = -10002;
global.USER_LOGIN_OTHER = -10003; //用户在其他设备上进行了登录
global.USER_LOGIN_SUCC = 10000; //用户登录成功
global.USER_LOGOUT_SUCC = 10001;

// 客户端发起的错误码
global.CLIENT_USER_LOGIN = 20000;
global.CLIENT_USER_LOGOUT = 20001;




exports.CallStatus = CallStatus