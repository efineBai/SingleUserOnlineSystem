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

#endif /* GlobalData_hpp */
namespace GlobalData{
const int USER_PWD_ERROR = -10001;
const int USER_NOT_EXIST = -10002;
const int USER_LOGIN_OTHER = -10003; //用户在其他设备上进行了登录
const int USER_LOGIN_SUCC = 10000; //用户登录成功
const int USER_LOGOUT_SUCC = 10001;

// 客户端发起的错误码
const int CLIENT_USER_LOGIN = 20000;
const int CLIENT_USER_LOGOUT = 20001;
}
