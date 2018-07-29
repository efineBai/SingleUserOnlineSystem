// global.RSA_PUB_KEY = ;
// global.RSA_PRI_KEY = ;
global.allUserCall = new Map();
global.allcheckingUser = new Map();

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
global.USER_STATUS_CHECK = 10002;

// 客户端发起的错误码
global.CLIENT_USER_LOGIN = 20000;
global.CLIENT_USER_LOGOUT = 20001;
global.CLIENT_KEEP_ALIVE =20002; // 用来回应服务端，客户端alive


global.private_key = "-----BEGIN PRIVATE KEY-----\n" +
    "MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBAKVnkb/BNFwSpfqA\n" +
    "zHx8T2udBmKc8iemV5E/eQcly/jxDcSnCfz9arIpfYiZ3EcnYNOjToVGzc7tOPxK\n" +
    "7j++t0WszjAyIkQB731jrZy/tfimyx7LEvWTFxBJ2BnbCLIoyt9XZcwJKmWqd2CT\n" +
    "TIlq/+Xvgytz9H31KSYzisiuzqwtAgMBAAECgYAMwBsgKQicQGPDF8KrpfmJViVz\n" +
    "3J1eKRh+/eGah3Nd0Vc6XZYLho1/BmvC5/lvEr4IEoKvC3I6DVdjO3N6Pn1qJdMI\n" +
    "t31l4v0+MDep7Oxq6VIeXOqtTLjkoOKvdDMJdprHQOnWk+1iFfMOZQfEpTGt5FM2\n" +
    "/SYGcCb31+ZAT6OTEQJBANazbnOUR5J+JEDiJCSE3Q2JrjjP+4fJODCdDXj3TLKh\n" +
    "8+I6UJHPB41FclzO5LuaJ7etSlVrRjokZ/JcASXF9csCQQDFOKBf/jUrYeJIzpsI\n" +
    "ur55lV7Ih8easutDoMhVx7whbB6NPCD55Hz1ARB2onLGLxABDXOlriDrMB6XOH97\n" +
    "3WbnAkEAyQy5b235H8sTs9aQNcpdHeJBzV2lkt/wyEUpao9ZuSVDNiOZcxDFZ5sS\n" +
    "nqn3M14Ft1CE/Tw5RRT2adOSF4cqxQJBALTBFnOER/TPzJYQDZVtmh9S4EEH+M/3\n" +
    "BZrA5HuCCRHUxxeIsWx2lnPymsUwU+MBxThBvOlvcyo6uv67wFOk8qcCQHaPgiLd\n" +
    "TTzIq4Wq+9+iA8okg6lxu76s1c0wh0lX9jACYPeEbTSg51T+foob7XO0ct8pI20f\n" +
    "LQO2EkquxZL8UZM=\n" +
    "-----END PRIVATE KEY-----\n"



glbal.public_key = "-----BEGIN PUBLIC KEY-----\n" +
    "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQClZ5G/wTRcEqX6gMx8fE9rnQZi\n" +
    "nPInpleRP3kHJcv48Q3Epwn8/WqyKX2ImdxHJ2DTo06FRs3O7Tj8Su4/vrdFrM4w\n" +
    "MiJEAe99Y62cv7X4psseyxL1kxcQSdgZ2wiyKMrfV2XMCSplqndgk0yJav/l74Mr\n" +
    "c/R99SkmM4rIrs6sLQIDAQAB\n" +
    "-----END PUBLIC KEY-----";


exports.CallStatus = CallStatus