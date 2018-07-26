//
//  user_login_djinni_impl.cpp
//  SingleUserOnlineClient
//
//  Created by castlebai on 26/7/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#include <stdio.h>
#include "user_login.hpp"
#include "single_user_online_client.hpp"

int32_t UserLogin::UserLogin::sign_up(const std::string &user_name, const std::string &pwd, const std::shared_ptr<LoginStatusCallback> &callback){
    std::shared_ptr<Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    string db;
    SingleUserOnlineStub stub(channel, db);
    
    stub.SignUp(user_name, pwd, callback);

    return -1;
}


int32_t UserLogin::UserLogin::login(const std::string & user_name, const std::string & pwd, const std::shared_ptr<LoginStatusCallback> & callback){
    std::shared_ptr<Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    string db;
    SingleUserOnlineStub stub(channel, db);
    stub.keepAliveStream(user_name, pwd, callback);
}
