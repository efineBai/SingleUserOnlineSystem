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
    stub_->signUp(&context, loginInfo, &resultInfo);
    switch (resultInfo.resultcode()) {
        case GlobalData::USER_LOGIN_SUCC:
            callback->onLoginSucc();
        break;
        case GlobalData::USER_PWD_ERROR:
            callback->onLoginFailed();
        default:
            callback->onLoginFailed();
        break;
    }
    cout<<resultInfo.resultcode()<<endl;
    cout<<resultInfo.resultmsg()<<endl;
    return false;
}

bool SingleUserOnlineStub::keepAliveStream(const string userName,const  string pwd,const  std::shared_ptr<LoginStatusCallback> & callback){
    ClientContext context;
    LoginInfo loginInfo;
    loginInfo.set_userid(userName);
    loginInfo.set_passwordencoded(pwd);
    
    // 声明一个writer, 用来向svr发送数据
    std:shared_ptr<ClientReaderWriter<LoginInfo, LoginInfo>> stream(stub_->keepAliveStream(&context));
    
    // first, client send logininfo to svr to start a connection
    if(!stream->Write(loginInfo)){
        //broken stream,
        cerr<< "broken stream"<<endl;
        return false;
    } else {
        cout<< "start waiting for response"<<endl;
        while(stream->Read(&loginInfo)){
            cout<< "start in new loop"<<endl;
            cout<< "get response "<< loginInfo.status()<< endl;
            cout<<"keepAlive Stream"<<endl;
            cout<< loginInfo.userid()<<endl;
            cout<< loginInfo.status()<<endl;
            if(loginInfo.status() == 1) {
                // svr发起对客户端的校验
                if(!stream->Write(loginInfo)){
                    //broken stream,
                    callback->onLoginFailed();
                    return false;
                } else{
                    // send login info succ
                    callback->onLoginSucc();
                }
                
            } else if(loginInfo.status() == 10000){
                // svr verify logininfo success
                // pass; do nothing
            } else {
                // error occurs; login status broken
                callback->onLoginOut();
                cout<< "user has been kicked out" << endl;
                
            }
        }
        cout<< "loop has been finished"<<endl;
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

