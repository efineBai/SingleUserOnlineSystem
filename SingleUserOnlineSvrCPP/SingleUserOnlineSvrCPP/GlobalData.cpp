//
//  GlobalData.cpp
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 14/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#include "GlobalData.hpp"
namespace GlobalData{
    std::map<std::string, StreamStatus>* allUserAlive = new std::map<std::string,StreamStatus>;
}
