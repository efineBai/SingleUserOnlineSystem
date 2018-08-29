 //
//  SingleUserOnlineService.cpp
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 9/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#define BCRYPT_HASHSIZE 64
#include "proto/single_user_online.grpc.pb.h"

#include <grpc++/grpc++.h>
#include "db_operation/SingleUserDbOperation.hpp"
#include <vector>
#include "GlobalData.hpp"
#include <regex>
#include <thread>
#include <chrono>
#include "tools/CommTools.hpp"
#include <unistd.h>
#include <time.h>
#include "bcrypt.h"

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
        char salt[64];
        char hash[64];
        bcrypt_gensalt(12, salt);
        bcrypt_hashpw(pwd.c_str(), salt, hash);
        if(!SingleUserDBOperation::getInstance()->insertNewUser(request->userid(), hash, salt)){
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
            
            // 首先判断客户端的发送的状态码
            
            //如果是获取token
            if(clientLoginInfo.status() == GlobalData::CLIENT_GET_TOKEN){
                //先将dbpwd 与 salt 获取到，然后存储到内存中
                string dbPwd, salt;
                if(!SingleUserDBOperation::getInstance()->queryUserPwd(clientLoginInfo.userid(), dbPwd, salt)){
                    //用户存在，开始校验密码的过程
                    cout<< "query user succ"<< clientLoginInfo.userid()<<endl;
                    if(GlobalData::tryLoginUser->find(clientLoginInfo.userid()) != GlobalData::tryLoginUser->end()){
                        // 如果当前用户之前已经有正在登陆的连接，情况比较多，暂时先丢弃当前请求，等待10s,如果该用户还在tryloginUser中，则将该记录直接删除，防止之前登陆中断后，无法再次登陆
                        //先丢弃当前请求
                        singleuseronline::LoginInfo svrLoginInfo;
                        svrLoginInfo.set_userid(clientLoginInfo.userid());
                        svrLoginInfo.set_status(GlobalData::USER_LOGIN_OTHER);
                        (*stream).ServerReaderWriter::Write(svrLoginInfo);
                        //等待10s
                        std::this_thread::sleep_for(std::chrono::seconds(10));
                        //再次检查
                         if(GlobalData::tryLoginUser->find(clientLoginInfo.userid()) != GlobalData::tryLoginUser->end()){
                             GlobalData::tryLoginUser->erase(clientLoginInfo.userid());
                         }
                        //直接中断连接
                        break;
                    }
                    
                    //当前该用户没有正在验证中
                    string token = CommTools::generateToken();
                    cout<<"create new status : salt:"<<salt<<";token:"<<token<<endl;
                    StreamStatus status(stream, dbPwd, salt, token);
                    (*GlobalData::tryLoginUser)[clientLoginInfo.userid()] = status;
                    LoginInfo svrLoginfo;
                    svrLoginfo.set_status(GlobalData::USER_STATUS_TOKEN);
                    svrLoginfo.set_deviceid(token);
                    svrLoginfo.set_passwordencoded(salt);
                    (*stream).ServerReaderWriter::Write(svrLoginfo);
                } else {
                    // 当前用户不存在
                    singleuseronline::LoginInfo svrLoginInfo;
                    svrLoginInfo.set_userid(clientLoginInfo.userid());
                    svrLoginInfo.set_status(GlobalData::USER_NOT_EXIST);
                    (*stream).ServerReaderWriter::Write(svrLoginInfo);
                    continue;
                }
            }
            // 如果是验证密码
            else if(clientLoginInfo.status() == GlobalData::CLIENT_USER_LOGIN){
                //查看是否是以及获取了token
                if(GlobalData::tryLoginUser->find(clientLoginInfo.userid()) != GlobalData::tryLoginUser->end()){
                    string dbpwd = (*GlobalData::tryLoginUser)[clientLoginInfo.userid()].dbpwd;
                    string token = (*GlobalData::tryLoginUser)[clientLoginInfo.userid()].token;
                    string encoded_dbpwd = CommTools::Sha256(dbpwd+token);
                    StreamStatus status = (*GlobalData::tryLoginUser)[clientLoginInfo.userid()];
                    if(encoded_dbpwd.compare(clientLoginInfo.passwordencoded())==0){
                        // 密码匹配成功,先查询是否有已经登陆的该用户
                        std::map<string, StreamStatus>::const_iterator it;
                        it = GlobalData::allUserAlive->find(clientLoginInfo.userid());
                        if(it != GlobalData::allUserAlive->end()){
                            //之前该用户已经登录过；则先将之前的登录退出
                            singleuseronline::LoginInfo logininfo;
                            logininfo.set_userid(clientLoginInfo.userid());
                            logininfo.set_status(GlobalData::USER_LOGIN_OTHER);
                            cout<<"last stream:"<<it->second.stream<<"; new stream"<< stream<<endl;
                            int ret = it->second.stream->ServerReaderWriter::Write(logininfo);
                            cout<<"lastStream logout :"<<ret<<endl;
                        }
                        
                        //当前用户登录成功，添加到已经登录成功的用户列表中
                        GlobalData::DeleteFromAllUser(clientLoginInfo.userid());//GlobalData::allUserAlive->erase(clientLoginInfo.userid());
                        (*GlobalData::allUserAlive)[clientLoginInfo.userid()] = status;
                        //从正在建立连接的用户中去掉该用户
                        GlobalData::tryLoginUser->erase(clientLoginInfo.userid());
                        singleuseronline::LoginInfo svrLoginInfo;
                        svrLoginInfo.set_userid(clientLoginInfo.userid());
                        svrLoginInfo.set_status(GlobalData::USER_LOGIN_SUCC);
                        (*stream).ServerReaderWriter::Write(svrLoginInfo);
                        
                    } else {
                        // 用户密码校验失败
                        GlobalData::tryLoginUser->erase(clientLoginInfo.userid());
                        singleuseronline::LoginInfo svrLoginInfo;
                        svrLoginInfo.set_userid(clientLoginInfo.userid());
                        svrLoginInfo.set_status(GlobalData::USER_PWD_ERROR);
                        (*stream).ServerReaderWriter::Write(svrLoginInfo);
                    }
                } else {
                    //还未获取token，丢弃请求
                    break;
                }
            }
           

        } //while()
       
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
            rules.clear();
            SingleUserDBOperation::getInstance()->queryRules(rules);
            if(rules.size() > 0) {
                //查找到了规则，进行遍历并踢出
                std::map<string, StreamStatus>::iterator it = GlobalData::allUserAlive->begin();
                vector<string> mNeedErase;
                mNeedErase.clear();
                while(it != GlobalData::allUserAlive->end()){
                    string userid = it->first;
                    // 将用户名与每一条规则进行匹配
                    for (vector<string>::const_iterator iter = rules.begin(); iter != rules.end();iter++){
                        cout<<"[rules] found:"<< *iter<<"size:"<<rules.size()<<endl;
                        if(std::regex_match(userid, std::regex(*iter))){
                            try{
                                cout<<"user matched"<<endl;
                                singleuseronline::LoginInfo lastLoginInfo;
                                lastLoginInfo.set_userid(userid);
                                lastLoginInfo.set_status(GlobalData::USER_LOGIN_OTHER);
                                (*(it->second.stream)).ServerReaderWriter::Write(lastLoginInfo);
                                mNeedErase.push_back(userid);
                                cout<<"userid:"<<userid<<"matched:"<<*iter<<endl;
                            }catch(...){
                                GlobalData::DeleteFromAllUser(userid);//GlobalData::allUserAlive->erase(userid);
                                std::cerr<<"crash"<<endl;
                            }
                        }
                    }
                    cout<<"allUserAlive"<<it->first<<endl;
                    ++it;
                }
                for (vector<string>::const_iterator iter = mNeedErase.begin(); iter != mNeedErase.end();iter++){
                    if(GlobalData::allUserAlive->find(*iter) != GlobalData::allUserAlive->end()){
                       GlobalData::DeleteFromAllUser(*iter);// GlobalData::allUserAlive->erase(*iter);
                    }
                }
                
            }
            std::this_thread::sleep_for(std::chrono::seconds(50));
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
//    // 创建新用户
//    if(!SingleUserDBOperation::getInstance()->insertNewUser("123", "123")){
//        cout<< "insert user succ"<<endl;
//    } else {
//        cout<< "insert user failed"<<endl;
//    }
////    查询用户密码
//    string pwd;
//    if(!SingleUserDBOperation::getInstance()->queryUserPwd("123", pwd)){
//        cout<< "query user succ"<< pwd<<endl;
//    } else {
//        cout<< "insert user failed"<<endl;
//    }
////     获取用户踢出规则
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

//    char salt[64];
//    char hash[64];
//    int ret;
//     ret = bcrypt_gensalt(12, salt);
//    for(int i=0;i <5;i++){
//
//
//    cout<<salt<<endl;
//    ret = bcrypt_hashpw("asdfasdfa", salt, hash);
//    cout<<hash<<endl;
//        cout<<"--------------"<<endl;
//    }
    
    return 0;
}

