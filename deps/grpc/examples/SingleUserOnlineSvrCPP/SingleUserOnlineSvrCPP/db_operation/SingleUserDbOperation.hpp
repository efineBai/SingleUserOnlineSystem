//
//  SingleUserDbOperation.hpp
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 9/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#ifndef SingleUserDbOperation_hpp
#define SingleUserDbOperation_hpp

#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <vector>

using std::string;

class SingleUserDBOperation{
public:
    static SingleUserDBOperation* getInstance();
    ~SingleUserDBOperation();
    int insertNewUser(const string user_name, const string pwd);
    int queryUserPwd(string user_name, string& pwd);
    int queryRules(std::vector<string>& rules);
private:
    SingleUserDBOperation();
    static SingleUserDBOperation* dbInstance;
    MYSQL *conn;
};
 
#endif /* SingleUserDbOperation_hpp */
