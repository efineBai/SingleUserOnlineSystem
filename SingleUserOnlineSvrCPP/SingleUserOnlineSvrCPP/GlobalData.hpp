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
#include "proto/single_user_online.grpc.pb.h"
#include <string>

using singleuseronline::LoginInfo;
using grpc::ServerReaderWriter;
using std::string;

//记录全局数据
namespace GlobalData{
    
//    // svr端返回的错误码
//    const int USER_PWD_ERROR = -10001;
//    const int USER_NOT_EXIST = -10002;
//    const int USER_LOGIN_OTHER = -10003; //用户在其他设备上进行了登录
//    const int USER_SIGNUP_ERR = -10004;
//    const int USER_LOGIN_ILEAGAL = -10005;
//
//
//    const int USER_LOGIN_SUCC = 10000; //用户登录成功
//    const int USER_LOGOUT_SUCC = 10001;
//    const int USER_STATUS_CHECK_SUCC = 10002;
//    const int USER_SIGNUP_SUCC = 10003; // 用户注册成功
//    const int USER_STATUS_NEED_CHECK = 10004;
//    const int USER_STATUS_TOKEN  = 10005; //将token 传递给客户端
//
//
//    // 客户端发起的错误码
//    const int CLIENT_USER_LOGIN = 20000;
//    const int CLIENT_USER_LOGOUT = 20001;
//    const int CLIENT_NET_CONNECT_ERR = 20002;
//    const int CLIENT_UNKNOWN_ERR = 20003;
//    const int CLIENT_GET_TOKEN = 20004; // 登录之前先获取token
//    
    
    class StreamStatus{
    public:
        ::grpc::ServerReaderWriter< ::singleuseronline::LoginInfo, ::singleuseronline::LoginInfo>* stream;
        
        string salt;
        string dbpwd;
        string token;
        StreamStatus(::grpc::ServerReaderWriter< ::singleuseronline::LoginInfo, ::singleuseronline::LoginInfo>* stream, const string dbpwd, const string salt, const string token){
            this->stream = stream;
            this->salt = salt;
            this->dbpwd = dbpwd;
            this->token = token;
        }
        StreamStatus(){};
    };
    
    // svr的公钥
    const string PUBLIC_KEY = "-----BEGIN PUBLIC KEY-----"\
    "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQClZ5G/wTRcEqX6gMx8fE9rnQZi"\
    "nPInpleRP3kHJcv48Q3Epwn8/WqyKX2ImdxHJ2DTo06FRs3O7Tj8Su4/vrdFrM4w"\
    "MiJEAe99Y62cv7X4psseyxL1kxcQSdgZ2wiyKMrfV2XMCSplqndgk0yJav/l74Mr"\
    "c/R99SkmM4rIrs6sLQIDAQAB"\
    "-----END PUBLIC KEY-----";
    
    const string PRIVATE_KEY = "-----BEGIN PRIVATE KEY-----\nMIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBAKVnkb/BNFwSpfqA\nzHx8T2udBmKc8iemV5E/eQcly/jxDcSnCfz9arIpfYiZ3EcnYNOjToVGzc7tOPxK\n7j++t0WszjAyIkQB731jrZy/tfimyx7LEvWTFxBJ2BnbCLIoyt9XZcwJKmWqd2CT\nTIlq/+Xvgytz9H31KSYzisiuzqwtAgMBAAECgYAMwBsgKQicQGPDF8KrpfmJViVz\n3J1eKRh+/eGah3Nd0Vc6XZYLho1/BmvC5/lvEr4IEoKvC3I6DVdjO3N6Pn1qJdMI\nt31l4v0+MDep7Oxq6VIeXOqtTLjkoOKvdDMJdprHQOnWk+1iFfMOZQfEpTGt5FM2\n/SYGcCb31+ZAT6OTEQJBANazbnOUR5J+JEDiJCSE3Q2JrjjP+4fJODCdDXj3TLKh\n8+I6UJHPB41FclzO5LuaJ7etSlVrRjokZ/JcASXF9csCQQDFOKBf/jUrYeJIzpsI\nur55lV7Ih8easutDoMhVx7whbB6NPCD55Hz1ARB2onLGLxABDXOlriDrMB6XOH97\n3WbnAkEAyQy5b235H8sTs9aQNcpdHeJBzV2lkt/wyEUpao9ZuSVDNiOZcxDFZ5sS\nnqn3M14Ft1CE/Tw5RRT2adOSF4cqxQJBALTBFnOER/TPzJYQDZVtmh9S4EEH+M/3\nBZrA5HuCCRHUxxeIsWx2lnPymsUwU+MBxThBvOlvcyo6uv67wFOk8qcCQHaPgiLd\nTTzIq4Wq+9+iA8okg6lxu76s1c0wh0lX9jACYPeEbTSg51T+foob7XO0ct8pI20f\nLQO2EkquxZL8UZM=\n-----END PRIVATE KEY-----";
    
    //TODO 换一种rsa算法
    const string PUBLIC_KEY_PWD = "-----BEGIN PUBLIC KEY-----\nMIGeMA0GCSqGSIb3DQEBAQUAA4GMADCBiAKBgH7dJAGE+CP4q/xj+hbaS2he6h6F\ndf3cJdApRR/uJMIuz1M6pVuXAppyG4ivkmQouCaUX3mMGxYiSvn3VxBZZAly74ZR\nW42ELMHxqCjjoKRVskhPAnPLaA6hGcx0JTbRHIkOuBJfUjV86u8D/GVnz2Sfi1D+\nBs7qyDzWu+xCZvCnAgMBAAE=\n-----END PUBLIC KEY-----";
    
    const string SALT_PWD = "pVuXAppyG4ivkmQouCaUX3mMGxYiSvn3VxBZZAly74Z";
    // 记录当前可用的请求连接
   extern std::map<string, StreamStatus>* allUserAlive;
    extern std::map<string, StreamStatus>* tryLoginUser;
   extern void DeleteFromAllUser(string userid);
}


#endif /* GlobalData_h */
