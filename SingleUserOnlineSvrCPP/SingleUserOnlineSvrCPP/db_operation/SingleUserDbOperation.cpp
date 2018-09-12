//
//  SingleUserDbOperation.cpp
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 9/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#include "SingleUserDbOperation.hpp"
#include <sstream>

using namespace std;
SingleUserDBOperation* SingleUserDBOperation::dbInstance = new SingleUserDBOperation;

SingleUserDBOperation* SingleUserDBOperation::getInstance(){
    return dbInstance;
}

SingleUserDBOperation::SingleUserDBOperation(){
    conn = mysql_init(NULL);
    
    if(!mysql_real_connect(conn, "0.0.0.0", "castle", "testpwd", "singleuser", 3308, NULL, 0)){
        cerr<<"mysql connect error"<<endl;
        conn = NULL;
    }
}

SingleUserDBOperation::~SingleUserDBOperation(){
    if(conn != NULL) {
        mysql_close(conn);
    }
}

//创建一个新用户
int SingleUserDBOperation::insertNewUser(string user_name, string pwd, string salt){
    if(conn == NULL || pwd.length()==0) {
         cerr<<"conn is null, NEED CHECK!"<<endl;
        return -1;
    }
    
    //创建插入的sql语句
    stringstream sqlstream;
    sqlstream<<"insert into  singleuser.user_info (user_name, user_pwd, user_salt) values ('" <<user_name<<"','"
    <<pwd<<"', '"<<salt<<"');"<<endl;
    string sql = sqlstream.str();
    cout<<"create new user sql: "<<sql<<endl;
    
    if(mysql_query(conn, sql.c_str())){
        // 返回非0； sql 执行失败；
        //TODO 增加对错误码的分析来区分创建失败的原因
        cerr<<"create new user error [check sql] :"<<mysql_errno(conn)<<mysql_error(conn)<<endl;
        return -1;
    } else {
        cout<<"inser new user succ:"<<user_name<<endl;
        //创建新用户成功
//        res = mysql_use_result(conn);
//        if(res == NULL){
//            cerr<<"res is null"<<endl;
//            return -1;
//        }
//        while ((row = mysql_fetch_row(res)) != NULL){
//            cout<<row[0]<<endl;
//        }
    }
    return 0;
}

//查询用户的密码
int SingleUserDBOperation::queryUserPwd(string user_name, string &pwd, string& salt){
    if(conn == NULL) {
         cerr<<"conn is null, NEED CHECK!"<<endl;
        return -1;
    }
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    //创建查询的sql语句
    stringstream sqlstream;
    sqlstream<<"select user_pwd, user_salt from singleuser.user_info where user_name = '"<<user_name<<"';";
    string sql = sqlstream.str();
    cout<<"query pwd of user:"<<user_name<<endl;
    
    if(mysql_query(conn, sql.c_str())){
        // 返回非0； sql 执行失败；
        //TODO 增加对错误码的分析来区分创建失败的原因
        cerr<<"query pwd error [check sql] :"<<mysql_errno(conn)<<mysql_error(conn)<<endl;
        return -1;
    } else {
        cout<<"query pwd succ:"<<user_name<<endl;
        res = mysql_use_result(conn);
        if(res == NULL){
            cerr<<"res is null"<<endl;
            return -1;
        }
        row = mysql_fetch_row(res);
        if(row == NULL ) {
            return -1;
        }
        cout<<"query result "<<row[0]<<"&"<<row[1]<<endl;
        pwd = row[0];
        salt = row[1];
        mysql_free_result(res);
    }
    
    return 0;
    
}

//查询用户踢出规则
int SingleUserDBOperation::queryRules(std::vector<string> &rules){
    // 先清空rules
    rules.clear();
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    //创建查询的sql语句
    stringstream sqlstream;
    sqlstream<<"select * from singleuser.user_forbid;";
    string sql = sqlstream.str();
    if(conn == NULL){
        cerr<<"conn is null, NEED CHECK!"<<endl;
        return -1;
    }
    if(mysql_query(conn, sql.c_str())){
        cerr<<"load rules error :"<<mysql_errno(conn)<<mysql_error(conn)<<endl;
    } else {
        cout<<"load rules succ ";
        res = mysql_use_result(conn);
        if(res == NULL){
            cerr<<"res is null"<<endl;
            return -1;
        }
        
        //读取查询到的结果
        while((row = mysql_fetch_row(res)) != NULL) {
            cout<<"[rules]"<<row[1]<<endl;
            rules.push_back(row[1]);
        }
        mysql_free_result(res);
    }
    
    return 0;
}
