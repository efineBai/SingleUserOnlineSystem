//
//  gRPCStubService.cpp
//  SingleUserOnlineClient
//
//  Created by castlebai on 22/7/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//
#include <iostream>
#include <thread>
#include "single_user_online_client.hpp"
#include "GlobalData.hpp"
#include "bcrypt.h"


using namespace std;

bool SingleUserOnlineStub::SignUp(const string userName, const string pwd, const std::shared_ptr<LoginStatusCallback> & callback) {
    ClientContext context;
    LoginInfo loginInfo ;
    loginInfo.set_userid(userName.c_str());
    loginInfo.set_passwordencoded(pwd.c_str());
    ResultInfo resultInfo;
    resultInfo.set_resultcode(singleuseronline::CLIENT_UNKNOWN_ERR);
    stub_->signUp(&context, loginInfo, &resultInfo);
    LOGD("SignUp result:ret %d, msg %s", resultInfo.resultcode(), resultInfo.resultmsg().c_str());
    switch (resultInfo.resultcode()) {
        case singleuseronline::USER_LOGIN_SUCC:
            callback->onLoginSucc();
            break;
        case singleuseronline::USER_PWD_ERROR:
            callback->onSignUpFailed(resultInfo.resultcode(),resultInfo.resultmsg());
            break;
        case singleuseronline::USER_SIGNUP_SUCC:
            callback->onSignUpSucc();
            break;
        
        default:
            callback->onSignUpFailed(resultInfo.resultcode(), resultInfo.resultmsg());
            break;
    }
    cout<<"sign up "<<resultInfo.resultcode()<<endl;
    cout<<resultInfo.resultmsg()<<endl;
    return false;
}

bool SingleUserOnlineStub::keepAliveStream(const string userName,const  string pwd, const string time_stamp, const  std::shared_ptr<LoginStatusCallback> & callback){
    ClientContext context;
    
    gpr_timespec timespec;
    timespec.tv_sec = 200;//设置阻塞时间为2秒
    timespec.tv_nsec = 0;
    timespec.clock_type = GPR_TIMESPAN;
    context.set_deadline(timespec);
    LoginInfo loginInfo;
    loginInfo.set_status(singleuseronline::CLIENT_GET_TOKEN);
    loginInfo.set_userid(userName);
    loginInfo.set_timestamp(time_stamp);
    
    
    // 声明一个writer, 用来向svr发送数据
    std:shared_ptr<ClientReaderWriter<LoginInfo, LoginInfo>> stream(stub_->keepAliveStream(&context));
    
    // first, client send logininfo to svr to start a connection
    if(!stream->Write(loginInfo)){
        //broken stream,
        cerr<< "broken stream"<<endl;
        return false;
    } else {
        LoginInfo retInfo;
        cout<< "start waiting for response"<<endl;
        while(stream->Read(&retInfo)){
            cout<< "start in new loop"<<endl;
            cout<< "get response "<< loginInfo.status()<< endl;
            cout<<"keepAlive Stream"<<endl;
            LOGD("%s",retInfo.userid().c_str());
            LOGD("%d",retInfo.status());
            string pwdParsed;
            LoginInfo clientInfo;
            switch (retInfo.status()) {
                case singleuseronline::USER_STATUS_NEED_CHECK:
                    // svr发起对客户端的校验
                    if(!stream->Write(loginInfo)){
                        //broken stream,
                        callback->onLoginFailed(singleuseronline::CLIENT_NET_CONNECT_ERR, "please check network");
                        return false;
                    } else{
                        // send login info succ
                        callback->onLoginSucc();
                    }
                    break;

                case singleuseronline::USER_NOT_EXIST:
                    stream->WritesDone();
                    stream->Finish();
                    callback->onLoginFailed(retInfo.status(), "用户不存在" );
                    return false;
                    break;
                case singleuseronline::USER_PWD_ERROR:
                    stream->WritesDone();
                       stream->Finish();
                    callback->onLoginFailed(retInfo.status(), "账号或密码错误");
                    return false;
                    break;
                case singleuseronline::USER_STATUS_CHECK_SUCC:
                    // do nothin ; 用户的心跳检查成功
                    break;
                case singleuseronline::USER_LOGIN_SUCC:
                    callback->onLoginSucc();
                   
                    break;
                case singleuseronline::USER_STATUS_TOKEN:
                    retInfo.passwordencoded();
                    char hash[64];
                    bcrypt_hashpw(pwd.c_str(), retInfo.passwordencoded().c_str(), hash);
                    pwdParsed = CommTools::Sha256(string(hash) + retInfo.deviceid());
                    clientInfo.set_userid(userName);
                    clientInfo.set_passwordencoded(pwdParsed);
                    clientInfo.set_status(singleuseronline::CLIENT_USER_LOGIN);
                    stream->Write(clientInfo);
                    //                    string token2 = retInfo.deviceid();
//                    string hash = CommTools::generateDbPwd(pwd, salt);
//                    string pwdhash = CommTools::Sha256(hash+token);
                    
                    break;
                default:
                    callback->onLoginOut(singleuseronline::CLIENT_UNKNOWN_ERR, "connection broken");
                    cout<< "user has been kicked out" << endl;
                    break;
            }
         
        }
        LOGD("while loop finished");
        return false;
    }
    
    return true;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    
    string name = "clientuser";
    string pwd = "clientpwd";
    
    return 0;
}

