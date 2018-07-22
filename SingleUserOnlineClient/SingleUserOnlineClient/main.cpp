//
//  main.cpp
//  SingleUserOnlineClient
//
//  Created by castlebai on 22/7/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#include <string>
#include "single_user_online_client.hpp"

using std::string;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::shared_ptr<Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    string db;
    SingleUserOnlineStub stub(channel, db);
    string name = "clientuser";
    string pwd = "clientpwd";
    stub.SignUp(name, pwd);

    return 0;
}
