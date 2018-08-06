//
//  gRPCStubService.hpp
//  SingleUserOnlineClient
//
//  Created by castlebai on 22/7/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#ifndef gRPCStubService_hpp
#define gRPCStubService_hpp

#include <stdio.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "single_user_online.grpc.pb.h"
#include "../generated-src/cpp/login_status_callback.hpp"


using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using singleuseronline::SingleUserOnline;
using singleuseronline::LoginInfo;
using singleuseronline::ResultInfo;
using std::string;
using UserLogin::LoginStatusCallback;

/*
 * 创建并封装gRPC的接口
 */
class SingleUserOnlineStub
{
public:
    SingleUserOnlineStub(std::shared_ptr<Channel> channel, const std::string& db)
            :stub_(SingleUserOnline::NewStub(channel)){

    }

    /*
     * 用来注册新用户
     */
    bool SignUp(const string userName, const string pwd, const std::shared_ptr<LoginStatusCallback> & callback);
    /*
     * 用来保成登录状态一直有效
     */
    bool keepAliveStream(const string userName, const string pwd, const string time_stamp, const std::shared_ptr<LoginStatusCallback> & callback);

    bool logout();


private:
    std::unique_ptr<SingleUserOnline::Stub> stub_;
    std::shared_ptr<ClientReaderWriter<LoginInfo, LoginInfo>> currentStream;


};
#endif /* gRPCStubService_hpp */

