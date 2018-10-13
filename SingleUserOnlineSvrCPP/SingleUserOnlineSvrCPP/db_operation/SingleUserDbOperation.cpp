//
//  SingleUserDbOperation.cpp
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 9/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//
#include "SingleUserDbOperation.hpp"
#include <sstream>

#define PWD_SIZE 256
#define SALT_SIZE 32

using namespace std;
SingleUserDBOperation* SingleUserDBOperation::dbInstance = new SingleUserDBOperation;

SingleUserDBOperation* SingleUserDBOperation::getInstance(){
    return dbInstance;
}

SingleUserDBOperation::SingleUserDBOperation(){
    conn = mysql_init(NULL);
    
    if(!mysql_real_connect(conn, "0.0.0.0", "castle", "testpwd", "singleuser", 3307, NULL, 0)){
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
//    stringstream sqlstream;
    char* sqlstream = "insert into  singleuser.user_info (user_name, user_pwd, user_salt) values (?, ?, ?);";
    MYSQL_STMT* stmt;
    stmt = mysql_stmt_init(conn);
    if (!stmt)
    {
        cerr<<" mysql_stmt_init(), out of memory"<<endl;
        exit(0);
    }
    
    if(mysql_stmt_prepare(stmt, sqlstream, strlen(sqlstream))){
        mysql_stmt_close(stmt);
        cerr<<"msyql_stmt_prepare error, please check sql"<<endl;
        return -1;
    } else {
        cout<<"pwd;salt : "<<pwd<<";"<<salt<<endl;
        MYSQL_BIND bind[3];
//        memset(bind, 0, sizeof(bind));
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (char*)user_name.data();
        unsigned long size_usr = user_name.length();
        bind[0].length = &size_usr;
        bind[0].is_null = 0;
        
        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = (char*)pwd.data();
        unsigned long size_pwd = pwd.length();
        bind[1].length = &size_pwd;
        bind[1].is_null = 0;

        bind[2].buffer_type = MYSQL_TYPE_STRING;
        bind[2].buffer = (char*)salt.data();
        unsigned long size_salt = salt.length();
        bind[2].length = &size_salt;
        bind[2].is_null = 0;
        
        if(mysql_stmt_bind_param(stmt, bind)) {
            cerr<<"mysql_stmt_bind_param error, please check params"<<endl;
            mysql_stmt_close(stmt);
            return -1;
        }
//
        cout<<"sql:"<<stmt->params<<endl;
        if(mysql_stmt_execute(stmt)){
            cerr<<"mysql_stmt_execute error, please check params:"<<mysql_error(conn)<<endl;
            mysql_stmt_close(stmt);
            return -1;
        }
        
        //数据插入成功
        cout<<"inser new user succ:"<<user_name<<endl;
        mysql_stmt_close(stmt);
        return 0;
        
    }
    
 
//    if(mysql_query(conn, sql.c_str())){
//        // 返回非0； sql 执行失败；
//        //TODO 增加对错误码的分析来区分创建失败的原因
//        cerr<<"create new user error [check sql] :"<<mysql_errno(conn)<<mysql_error(conn)<<endl;
//        return -1;
//    } else {
//        cout<<"inser new user succ:"<<user_name<<endl;
//        //创建新用户成功
////        res = mysql_use_result(conn);
////        if(res == NULL){
////            cerr<<"res is null"<<endl;
////            return -1;
////        }
////        while ((row = mysql_fetch_row(res)) != NULL){
////            cout<<row[0]<<endl;
////        }
//    }

}

//查询用户的密码 TODO 增加只查询用户存在既可以，不用查出来密码
int SingleUserDBOperation::queryUserPwd(string user_name, string &pwd_str, string& salt_str){
    if(conn == NULL) {
         cerr<<"conn is null, NEED CHECK!"<<endl;
        return -1;
    }
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    //创建查询的sql语句
    
    char* sqlstream = "select user_pwd, user_salt from singleuser.user_info where user_name = ?;";
   
    cout<<"query pwd of user:"<<user_name<<endl;
   
    MYSQL_STMT* stmt;
    stmt = mysql_stmt_init(conn);
    if (!stmt)
    {
        cerr<<" mysql_stmt_init(), out of memory"<<endl;
        exit(0);
    }
    
    if(mysql_stmt_prepare(stmt, sqlstream, strlen(sqlstream))){
        mysql_stmt_close(stmt);
        cerr<<"msyql_stmt_prepare error, please check sql"<<endl;
        return -1;
    } else {
        MYSQL_BIND bind[1];
        MYSQL_RES* res;
        //        memset(bind, 0, sizeof(bind));
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (char*)user_name.data();
        unsigned long size_usr = user_name.length();
        bind[0].length = &size_usr;
        bind[0].is_null = 0;
        
        if(mysql_stmt_bind_param(stmt, bind)) {
            cerr<<"mysql_stmt_bind_param error, please check params"<<endl;
            mysql_stmt_close(stmt);
            return -1;
        }
        
        
        if(mysql_stmt_execute(stmt)) {
            cerr<<"mysql_stmt_execute error, please check params"<<endl;
            mysql_stmt_close(stmt);
            return -1;
        }
        
        // 处理查询结果
        cout<<"query pwd succ:"<<user_name<<endl;
        
        MYSQL_BIND ret_bind[2];
        char pwd[PWD_SIZE];
        char salt[SALT_SIZE];
        unsigned long length[2];
        bool is_null[2];
        bool is_err[2];
        
        ret_bind[0].buffer_type = MYSQL_TYPE_STRING;
        ret_bind[0].buffer = pwd;
        ret_bind[0].length = &(length[0]);
        ret_bind[0].buffer_length = PWD_SIZE;
        ret_bind[0].is_null = is_null;
        ret_bind[0].error = is_err;
        
        ret_bind[1].buffer_type = MYSQL_TYPE_STRING;
        ret_bind[1].buffer = salt;
        ret_bind[1].length = &(length[1]);
        ret_bind[1].buffer_length = SALT_SIZE;
        ret_bind[1].is_null = &(is_null[1]);
        ret_bind[1].error = &(is_err[1]);
        
        /* Bind the result buffers */
        if (mysql_stmt_bind_result(stmt, ret_bind))
        {
            cerr<<" mysql_stmt_bind_result() failed"<<endl;
            return -1;
        }
        
        if (mysql_stmt_store_result(stmt))
        {
            cerr<<" mysql_stmt_bind_result() failed"<<endl;
            return -1;
        }
        fprintf(stdout, "Fetching results ...\n");
        if (!mysql_stmt_fetch(stmt))
        {
            if(is_null[0] || is_null[1]) {
                cerr<< "pwd or salt is null"<<endl;
                return -1;
            }
            pwd_str = pwd;
            salt_str = salt;
            return 0;
        }
    
    }
//    if(mysql_query(conn, sql.c_str())){
//        // 返回非0； sql 执行失败；
//        //TODO 增加对错误码的分析来区分创建失败的原因
//        cerr<<"query pwd error [check sql] :"<<mysql_errno(conn)<<mysql_error(conn)<<endl;
//        return -1;
//    } else {
//        cout<<"query pwd succ:"<<user_name<<endl;
//        res = mysql_use_result(conn);
//        if(res == NULL){
//            cerr<<"res is null"<<endl;
//            return -1;
//        }
//        row = mysql_fetch_row(res);
//        if(row == NULL ) {
//            return -1;
//        }
//        cout<<"query result "<<row[0]<<"&"<<row[1]<<endl;
//        pwd = row[0];
//        salt = row[1];
//        mysql_free_result(res);
//    }
    
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
