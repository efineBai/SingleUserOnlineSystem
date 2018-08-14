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
#include "tools/CommTools.hpp"
#include <unistd.h>


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
using GlobalData::StreamStatus;

::grpc::ServerReaderWriter< ::singleuseronline::LoginInfo, ::singleuseronline::LoginInfo>* stream2;
// 实现proto中定义的接口
class SingleUserOnlineServiceImpl final : public singleuseronline::SingleUserOnline::Service{
    // 注册新用户接口
    Status signUp(ServerContext* context,  const ::singleuseronline::LoginInfo* request, ::singleuseronline::ResultInfo* response){
         cout<< "new user signup"<<endl;
        
        // 先用私钥解密encoded pwd
        string pwd = CommTools::RsaDecode(request->passwordencoded());
        if(pwd.length() > 10) {
            // 去除拼接上的时间戳； TODO 可以增加对时间戳的判断
            pwd = pwd.substr(0, pwd.length()-10);
        } else {
            response->set_resultcode(GlobalData::USER_SIGNUP_ERR);
            response->set_resultmsg("pwd is empty");
            return Status::OK;
        }
        if(!SingleUserDBOperation::getInstance()->insertNewUser(request->userid(), CommTools::getMD5(CommTools::getMD5(pwd)+GlobalData::SALT_PWD))){
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
            cout<<"Thread is"<<std::this_thread::get_id()<<endl;
            cout<<"current stream:"<<stream<<endl;
            int iPid = (int)getpid();
            cout<<"Processid is "<< iPid<<endl;
            if(clientLoginInfo.userid().empty()){
               continue;
            }
           
            string dbPwd;
            if(!SingleUserDBOperation::getInstance()->queryUserPwd(clientLoginInfo.userid(), dbPwd)){
                cout<< "query user succ"<< dbPwd<<endl;
//                dbPwd = dbPwd + clientLoginInfo.timestamp();
//                dbPwd = CommTools::getMD5(dbPwd);
                string clientpwd = clientLoginInfo.passwordencoded();
                clientpwd = CommTools::RsaDecode(clientpwd);
                if(clientpwd.length() > 10) {
                    // 先得到md5值
                    cout<<"clientpwd"<<clientpwd<<endl;
                    clientpwd = clientpwd.substr(0, clientpwd.length() -10);
                    cout<<"clientpwd"<<clientpwd<<endl;
                    clientpwd = CommTools::getMD5(clientpwd + GlobalData::SALT_PWD);
                } else {
                    // 密码不对
                    singleuseronline::LoginInfo svrLoginInfo;
                    svrLoginInfo.set_userid(clientLoginInfo.userid());
                    svrLoginInfo.set_status(GlobalData::USER_PWD_ERROR);
                    (*stream).ServerReaderWriter::Write(svrLoginInfo);
                   
                }
                if(dbPwd.compare(clientpwd) == 0){
                    // 密码匹配成功,先查询是否有已经登陆的该用户
                    std::map<string, StreamStatus>::const_iterator it;
                    it = GlobalData::allUserAlive->find(clientLoginInfo.userid());
                    if(it != GlobalData::allUserAlive->end()){
                        //之前该用户已经登录过；则先将之前的登录退出
                        singleuseronline::LoginInfo logininfo;
                        logininfo.set_userid(clientLoginInfo.userid());
                        logininfo.set_status(GlobalData::USER_LOGIN_OTHER);
                        ::grpc::ServerReaderWriter< ::singleuseronline::LoginInfo, ::singleuseronline::LoginInfo>* lastStream = it->second.stream;
                        cout<<"last stream:"<<it->second.stream<<"; new stream"<< stream<<endl;
                        int ret = it->second.stream->ServerReaderWriter::Write(logininfo);
                        cout<<"lastStream logout :"<<ret<<endl;
                
                    }
                    
                    //当前用户登录成功
                    stream2 = stream;
                    GlobalData::allUserAlive->erase(clientLoginInfo.userid());
                    StreamStatus status(stream, clientLoginInfo);
                    (*GlobalData::allUserAlive)[clientLoginInfo.userid()] = status;
                    singleuseronline::LoginInfo svrLoginInfo;
                    svrLoginInfo.set_userid(clientLoginInfo.userid());
                    svrLoginInfo.set_status(GlobalData::USER_LOGIN_SUCC);
                    (*stream).ServerReaderWriter::Write(svrLoginInfo);
                  
                    continue;
                
                } else {
                    //密码不正确; 提示错误
                    singleuseronline::LoginInfo svrLoginInfo;
                    svrLoginInfo.set_userid(clientLoginInfo.userid());
                    svrLoginInfo.set_status(GlobalData::USER_PWD_ERROR);
                    (*stream).ServerReaderWriter::Write(svrLoginInfo);
                   continue;
                }
            } else {
                // 当前用户不存在
                singleuseronline::LoginInfo svrLoginInfo;
                svrLoginInfo.set_userid(clientLoginInfo.userid());
                svrLoginInfo.set_status(GlobalData::USER_NOT_EXIST);
                (*stream).ServerReaderWriter::Write(svrLoginInfo);
                continue;
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
                std::map<string, StreamStatus>::iterator it;
                it = GlobalData::allUserAlive->begin();
                while(it != GlobalData::allUserAlive->end()){
                    string userid = it->first;
                    // 将用户名与每一条规则进行匹配
                    for (vector<string>::const_iterator iter = rules.begin(); iter != rules.end();iter++){
                        cout<<"[rules] found:"<< *iter<<endl;
                        if(std::regex_match(userid, std::regex(*iter))){
                            try{
                                singleuseronline::LoginInfo lastLoginInfo;
                                lastLoginInfo.set_userid(userid);
                                lastLoginInfo.set_status(GlobalData::USER_LOGIN_OTHER);
                                ::grpc::ServerReaderWriter< ::singleuseronline::LoginInfo, ::singleuseronline::LoginInfo>* lastStream = it->second.stream;
                                (*(it->second.stream)).ServerReaderWriter::Write(lastLoginInfo);
                                GlobalData::allUserAlive->erase(userid);
                                cout<<"userid:"<<userid<<"matched:"<<*iter<<endl;
                            }catch(...){
                                GlobalData::allUserAlive->erase(userid);
                                std::cerr<<"crash"<<endl;
                            }
                        }
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    }
    
    // 用来启动 按规则踢出用户
    public :
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
//    std::vector<string> rules;
//    if(!SingleUserDBOperation::getInstance()->queryRules(rules)){
//        cout<< "query user forbid rules succ :"<< rules.size()<<endl;
//        for(int i=0; i< rules.size(); i++){
//            cout<<"[rule]"<< rules.at(i)<<endl;
//            cout<<std::regex_match("midas", std::regex( rules.at(i)))<<endl;
//            cout<<std::regex_match("a123s", std::regex( rules.at(i)))<<endl;
//        }
//    } else {
//        cout<< "insert user failed"<<endl;
//    }

    string db;
    std::string server_address("0.0.0.0:3001");
    SingleUserOnlineServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    service.KickoutForbidUserLauncher();
    server->Wait();
//
    
    return 0;
}

