//
//  user_login_djinni_impl.h
//  SingleUserOnlineClient
//
//  Created by castlebai on 5/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#ifndef user_login_djinni_impl_h
#define user_login_djinni_impl_h
#include "../generated-src/cpp/user_login.hpp"
#include "GlobalData.hpp"

namespace UserLogin{
    class UserLoginImpl : public UserLogin {
        public:
        ~UserLoginImpl(){};
        UserLoginImpl(){};
        virtual int32_t sign_up(const std::string & user_name, const std::string & pwd, const std::shared_ptr<LoginStatusCallback> & callback) override;
        
        virtual int32_t login(const std::string & user_name, const std::string & pwd, const std::shared_ptr<LoginStatusCallback> & callback) override;
        
        virtual int32_t logout(const std::string & user_name, const std::string & pwd, const std::shared_ptr<LoginStatusCallback> & callback) override;
 
    };
}



#endif /* user_login_djinni_impl_h */
