//
//  user_login_djinni_impl.cpp
//  SingleUserOnlineClient
//
//  Created by castlebai on 26/7/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#include <iostream>
#include "user_login_djinni_impl.h"
#include "single_user_online_client.hpp"
#include <ctime>
#include <string>
#include <sstream>
#include "CommTools.hpp"
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <ctime>


using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using std::cerr;
using std::cout;
using std::endl;


/*
 * 注册用户时，需要传递用户的密码，这时需要用服务端的publickey 进行加密
 */
namespace UserLogin {
    string srvaddr = "10.70.81.48:3001";
int32_t UserLoginImpl::sign_up(const std::string &user_name, const std::string &pwd, const std::shared_ptr<LoginStatusCallback> &callback){
    LOGD("user signup called in cpp1 %s", pwd.c_str());
    std::shared_ptr<Channel> channel = grpc::CreateChannel(srvaddr, grpc::InsecureChannelCredentials());
    if(channel == nullptr) {
        LOGD("channel create error");
    }
    string db;
    SingleUserOnlineStub stub(channel, db);
    std::time_t t = std::time(0);
    std::string pwd_salt = pwd + std::to_string(t);
    std::string encodedPwd = CommTools::RsaEncodeWithSvr(pwd_salt);
    LOGD("user signup called in cpp, pwd after encocded : %s", encodedPwd.c_str());
    stub.SignUp(user_name, encodedPwd, callback);

    return -1;
}

/*
 * 登录时，与后台通信不需要用密码，使用rsa(h(pwd)+ts)
 */
int32_t UserLoginImpl::login(const std::string & user_name, const std::string & pwd, const std::shared_ptr<LoginStatusCallback> & callback){
     LOGD("user login called in cpp1 %s", pwd.c_str());
    if(user_name.empty() || pwd.empty()) {
        if(callback != nullptr) {
            callback->onLoginFailed(singleuseronline::CLIENT_USER_LOGIN, "username or pwd is empty");
            cerr<<"user_name or pwd is empty";
        }
        return -1;
    }
    std::shared_ptr<Channel> channel = grpc::CreateChannel(srvaddr, grpc::InsecureChannelCredentials());
    string db;
    SingleUserOnlineStub stub(channel, db);
    
    std::time_t t = std::time(0);
    string ts = std::to_string(t);
    string p = pwd;
    p = CommTools::getMD5(p);
    p += ts;
    p = CommTools::RsaEncodeWithSvr(p);
    //string hex_p = CommTools::buff_to_hexstring(p.c_str(), (int)std::strlen(p.c_str()));
    LOGD("user pwd after hash add salt rsa: %s", p.c_str());
    stub.keepAliveStream(user_name, pwd, ts, callback);
    return -1;
}

    int32_t UserLoginImpl::logout(const std::string &user_name, const std::string &pwd, const std::shared_ptr<LoginStatusCallback> &callback){
        return -1;
    }
    
    std::shared_ptr<UserLogin> UserLogin::createUserInterface(){
    return std::make_shared<UserLoginImpl>();
}
}

