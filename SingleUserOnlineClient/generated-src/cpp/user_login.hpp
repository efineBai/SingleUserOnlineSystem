// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from UserLogin.djinni

#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace UserLogin {

class LoginStatusCallback;

class UserLogin {
public:
    virtual ~UserLogin() {}

    virtual int32_t sign_up(const std::string & user_name, const std::string & pwd, const std::shared_ptr<LoginStatusCallback> & callback) = 0;

    virtual int32_t login(const std::string & user_name, const std::string & pwd, const std::shared_ptr<LoginStatusCallback> & callback) = 0;

    virtual int32_t logout(const std::string & user_name, const std::string & pwd, const std::shared_ptr<LoginStatusCallback> & callback) = 0;
};

}  // namespace UserLogin
