//
//  GlobalData.cpp
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 14/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#include "GlobalData.hpp"
#include <mutex>

std::mutex g_lock;

namespace GlobalData{
    std::map<std::string, StreamStatus>* allUserAlive = new std::map<std::string,StreamStatus>;
    std::map<std::string, StreamStatus>* tryLoginUser = new std::map<std::string,StreamStatus>;
    void DeleteFromAllUser(string userid){
        g_lock.lock();
        if(allUserAlive->find(userid) != allUserAlive->end()){
            allUserAlive->erase(userid);
        }
        g_lock.unlock();
    }
}
