//
//  GlobalData.hpp
//  SingleUserOnlineClient
//
//  Created by castlebai on 26/7/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#ifndef GlobalData_hpp
#define GlobalData_hpp

#include <stdio.h>
#include <string>

#include <android/log.h>
#define  LOG_TAG    "SingleUserOnline"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
//#define  LOGD(...)
using std::string;
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
    
}
#endif /* GlobalData_hpp */
