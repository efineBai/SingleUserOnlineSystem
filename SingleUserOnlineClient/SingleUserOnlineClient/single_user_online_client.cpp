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



using namespace std;
bool SingleUserOnlineStub::SignUp(const string userName, const string pwd, const std::shared_ptr<LoginStatusCallback> & callback) {
    ClientContext context;
    LoginInfo loginInfo ;
    loginInfo.set_userid(userName.c_str());
    loginInfo.set_passwordencoded(pwd.c_str());
    ResultInfo resultInfo;
    resultInfo.set_resultcode(GlobalData::CLIENT_UNKNOWN_ERR);
    stub_->signUp(&context, loginInfo, &resultInfo);
    LOGD("SignUp result:ret %d, msg %s", resultInfo.resultcode(), resultInfo.resultmsg().c_str());
    switch (resultInfo.resultcode()) {
        case GlobalData::USER_LOGIN_SUCC:
            callback->onLoginSucc();
            break;
        case GlobalData::USER_PWD_ERROR:
            callback->onSignUpFailed(resultInfo.resultcode(),resultInfo.resultmsg());
            break;
        case GlobalData::USER_SIGNUP_SUCC:
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
    loginInfo.set_userid(userName);
    loginInfo.set_passwordencoded(pwd);
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
            switch (retInfo.status()) {
                case GlobalData::USER_STATUS_NEED_CHECK:
                    // svr发起对客户端的校验
                    if(!stream->Write(loginInfo)){
                        //broken stream,
                        callback->onLoginFailed(GlobalData::CLIENT_NET_CONNECT_ERR, "please check network");
                        return false;
                    } else{
                        // send login info succ
                        callback->onLoginSucc();
                    }
                    break;
                case GlobalData::USER_NOT_EXIST:
                    stream->WritesDone();
                    stream->Finish();
                    callback->onLoginFailed(retInfo.status(), "用户不存在" );
                    return false;
                    break;
                case GlobalData::USER_PWD_ERROR:
                    stream->WritesDone();
                       stream->Finish();
                    callback->onLoginFailed(retInfo.status(), "账号或密码错误");
                    return false;
                    break;
                case GlobalData::USER_STATUS_CHECK_SUCC:
                    // do nothin ; 用户的心跳检查成功
                    break;
                case GlobalData::USER_LOGIN_SUCC:
                    callback->onLoginSucc();
                   
                    break;
                default:
                    callback->onLoginOut(GlobalData::CLIENT_UNKNOWN_ERR, "connection broken");
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

