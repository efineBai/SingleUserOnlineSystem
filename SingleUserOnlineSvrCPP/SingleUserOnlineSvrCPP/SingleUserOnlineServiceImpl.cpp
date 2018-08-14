//
//  SingleUserOnlineService.cpp
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 9/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//
#include "single_user_online.grpc.pb.h"
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include "db_operation/SingleUserDbOperation.hpp"
#include <vector>
#include "GlobalData.hpp"
#include <regex>
#include <thread>
#include <chrono>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using singleuseronline::LoginInfo;
using singleuseronline::ResultInfo;
using std::thread;

// 实现proto中定义的接口
class SingleUserOnlineServiceImpl final : public singleuseronline::SingleUserOnline::Service{
    
    // 注册新用户接口
    Status signUp(ServerContext* context,  const ::singleuseronline::LoginInfo* request, ::singleuseronline::ResultInfo* response){
        if(!SingleUserDBOperation::getInstance()->insertNewUser(request->userid(), request->passwordencoded())){
            cout<< "insert user succ"<<endl;
            response->set_resultcode(GlobalData::USER_SIGNUP_SUCC);
            response->set_resultmsg("create user succ");
        } else {
            response->set_resultcode(GlobalData::USER_SIGNUP_ERR);
            response->set_resultmsg("create user failed");
            cout<< "insert user failed"<<endl;
        }
        return Status::OK;
    }
    
    // 用户登录接口，使用stream to stream，可以使用户被踢出
    //TODO 可以增加每分钟做一次检活
    Status keepAliveStream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::singleuseronline::LoginInfo, ::singleuseronline::LoginInfo>* stream){
        string pwd;
        LoginInfo clientLoginInfo;
        while(stream->Read(&clientLoginInfo)){
            singleuseronline::LoginInfo svrLoginInfo;
            if(clientLoginInfo.userid().empty()){
                break;
            }
            svrLoginInfo.set_userid(clientLoginInfo.userid());
            string dbPwd;
            if(!SingleUserDBOperation::getInstance()->queryUserPwd(clientLoginInfo.userid(), dbPwd)){
                cout<< "query user succ"<< dbPwd<<endl;
                if(dbPwd.compare(clientLoginInfo.passwordencoded()) == 0){
                    // 密码匹配成功,先查询是否有已经登陆的该用户
                    std::map<string, ServerReaderWriter< LoginInfo, LoginInfo>*>::const_iterator it;
                    it = GlobalData::allUserAlive.find(clientLoginInfo.userid());
                    if(it != GlobalData::allUserAlive.end()){
                        //之前该用户已经登录过；则先将之前的登录退出
                        singleuseronline::LoginInfo lastLoginInfo;
                        lastLoginInfo.set_userid(clientLoginInfo.userid());
                        lastLoginInfo.set_status(GlobalData::USER_LOGIN_OTHER);
                        (*(it->second)).ServerReaderWriter::Write(lastLoginInfo);
                    }
                    
                    //当前用户登录成功
                    GlobalData::allUserAlive[clientLoginInfo.userid()] = stream;
                    svrLoginInfo.set_status(GlobalData::USER_LOGIN_SUCC);
                    (*stream).ServerReaderWriter::Write(svrLoginInfo);
                    break;
                
                } else {
                    //密码不正确; 提示错误
                    svrLoginInfo.set_status(GlobalData::USER_PWD_ERROR);
                    (*stream).ServerReaderWriter::Write(svrLoginInfo);
                    break;
                }
            } else {
                // 当前用户不存在
                svrLoginInfo.set_status(GlobalData::USER_NOT_EXIST);
                (*stream).ServerReaderWriter::Write(svrLoginInfo);
                break;
            }
        }
       
        return Status::OK;
    }
    
    Status keepAliveShort(::grpc::ServerContext* context, const ::singleuseronline::LoginInfo* request, ::singleuseronline::ResultInfo* response){
        //暂时先不使用
        return Status::OK;
    }
    
    
    // 定时读取规则，踢出非法用户； 不要直接调用
    static void KickoutForbidUser(){
        while(true){
            vector<string> rules ;
            SingleUserDBOperation::getInstance()->queryRules(rules);
            if(rules.size() > 0) {
                //查找到了规则，进行遍历并踢出
                std::map<string, ServerReaderWriter< LoginInfo, LoginInfo>*>::iterator it;
                it = GlobalData::allUserAlive.begin();
                while(it != GlobalData::allUserAlive.end()){
                    string userid = it->first;
                    // 将用户名与每一条规则进行匹配
                    for (vector<string>::const_iterator iter = rules.begin(); iter != rules.end();iter++){
                        cout<<"[rules] found:"<< *iter<<endl;
                        if(std::regex_match(userid, std::regex(*iter))){
                            singleuseronline::LoginInfo lastLoginInfo;
                            lastLoginInfo.set_userid(userid);
                            lastLoginInfo.set_status(GlobalData::USER_LOGIN_OTHER);
                            (*(it->second)).ServerReaderWriter::Write(lastLoginInfo);
                            GlobalData::allUserAlive.erase(userid);
                            cout<<"userid:"<<userid<<"matched:"<<*iter<<endl;
                        }
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(60));
        }
    }
    
    // 用来启动 按规则踢出用户
    void KickoutForbidUserLauncher(){
        thread t(KickoutForbidUser);
        t.detach();
    }
    
};


int main(int argc, const char * argv[]) {
    // 创建新用户
//    if(!SingleUserDBOperation::getInstance()->insertNewUser("123", "123")){
//        cout<< "insert user succ"<<endl;
//    } else {
//        cout<< "insert user failed"<<endl;
//    }
    //查询用户密码
//    string pwd;
//    if(!SingleUserDBOperation::getInstance()->queryUserPwd("123", pwd)){
//        cout<< "query user succ"<< pwd<<endl;
//    } else {
//        cout<< "insert user failed"<<endl;
//    }
    // 获取用户踢出规则
    std::vector<string> rules;
    if(!SingleUserDBOperation::getInstance()->queryRules(rules)){
        cout<< "query user forbid rules succ :"<< rules.size()<<endl;
        for(int i=0; i< rules.size(); i++){
            cout<<"[rule]"<< rules.at(i)<<endl;
            cout<<std::regex_match("midas", std::regex( rules.at(i)))<<endl;
            cout<<std::regex_match("a123s", std::regex( rules.at(i)))<<endl;
        }
    } else {
        cout<< "insert user failed"<<endl;
    }

    string db;
    std::string server_address("0.0.0.0:3001");
    SingleUserOnlineServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
//
    
    return 0;
}

