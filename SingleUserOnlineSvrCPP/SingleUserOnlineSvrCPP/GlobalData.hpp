//
//  GlobalData.h
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 12/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#ifndef GlobalData_h
#define GlobalData_h

#include <map>
#include <grpc/grpc.h>
#include "single_user_online.grpc.pb.h"

using singleuseronline::LoginInfo;
using grpc::ServerReaderWriter;

//记录全局数据
namespace GlobalData{
    
    // svr端返回的错误码
    const int USER_PWD_ERROR = -10001;
    const int USER_NOT_EXIST = -10002;
    const int USER_LOGIN_OTHER = -10003; //用户在其他设备上进行了登录
    const int USER_SIGNUP_ERR = -10004;
    const int USER_LOGIN_ILEAGAL = -10005;
    
    
    const int USER_LOGIN_SUCC = 10000; //用户登录成功
    const int USER_LOGOUT_SUCC = 10001;
    const int USER_STATUS_CHECK_SUCC = 10002;
    const int USER_SIGNUP_SUCC = 10003; // 用户注册成功
    const int USER_STATUS_NEED_CHECK = 10004;
    
    
    // 客户端发起的错误码
    const int CLIENT_USER_LOGIN = 20000;
    const int CLIENT_USER_LOGOUT = 20001;
    const int CLIENT_NET_CONNECT_ERR = 20002;
    const int CLIENT_UNKNOWN_ERR = 20003;
    
    // svr的公钥
    const string PUBLIC_KEY = "-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQClZ5G/wTRcEqX6gMx8fE9rnQZi\nnPInpleRP3kHJcv48Q3Epwn8/WqyKX2ImdxHJ2DTo06FRs3O7Tj8Su4/vrdFrM4w\nMiJEAe99Y62cv7X4psseyxL1kxcQSdgZ2wiyKMrfV2XMCSplqndgk0yJav/l74Mr\nc/R99SkmM4rIrs6sLQIDAQAB\n-----END PUBLIC KEY-----";
    
    const string PRIVATE_KEY = "-----BEGIN PRIVATE KEY-----\nMIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBAKVnkb/BNFwSpfqAzHx8T2udBmKc8iemV5E/eQcly/jxDcSnCfz9arIpfYiZ3EcnYNOjToVGzc7tOPxK7j++t0WszjAyIkQB731jrZy/tfimyx7LEvWTFxBJ2BnbCLIoyt9XZcwJKmWqd2CTTIlq/+Xvgytz9H31KSYzisiuzqwtAgMBAAECgYAMwBsgKQicQGPDF8KrpfmJViVz3J1eKRh+/eGah3Nd0Vc6XZYLho1/BmvC5/lvEr4IEoKvC3I6DVdjO3N6Pn1qJdMIt31l4v0+MDep7Oxq6VIeXOqtTLjkoOKvdDMJdprHQOnWk+1iFfMOZQfEpTGt5FM2/SYGcCb31+ZAT6OTEQJBANazbnOUR5J+JEDiJCSE3Q2JrjjP+4fJODCdDXj3TLKh8+I6UJHPB41FclzO5LuaJ7etSlVrRjokZ/JcASXF9csCQQDFOKBf/jUrYeJIzpsIur55lV7Ih8easutDoMhVx7whbB6NPCD55Hz1ARB2onLGLxABDXOlriDrMB6XOH973WbnAkEAyQy5b235H8sTs9aQNcpdHeJBzV2lkt/wyEUpao9ZuSVDNiOZcxDFZ5sSnqn3M14Ft1CE/Tw5RRT2adOSF4cqxQJBALTBFnOER/TPzJYQDZVtmh9S4EEH+M/3BZrA5HuCCRHUxxeIsWx2lnPymsUwU+MBxThBvOlvcyo6uv67wFOk8qcCQHaPgiLdTTzIq4Wq+9+iA8okg6lxu76s1c0wh0lX9jACYPeEbTSg51T+foob7XO0ct8pI20fLQO2EkquxZL8UZM=\n-----END PRIVATE KEY-----";
    
    // 记录当前可用的请求连接
    std::map<string, ServerReaderWriter< LoginInfo, LoginInfo>*> allUserAlive;
    
}


#endif /* GlobalData_h */
