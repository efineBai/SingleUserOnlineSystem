// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from UserLogin.djinni

#pragma once

#include "djinni_support.hpp"
#include "user_login.hpp"

namespace djinni_generated {

class NativeUserLogin final : ::djinni::JniInterface<::UserLogin::UserLogin, NativeUserLogin> {
public:
    using CppType = std::shared_ptr<::UserLogin::UserLogin>;
    using CppOptType = std::shared_ptr<::UserLogin::UserLogin>;
    using JniType = jobject;

    using Boxed = NativeUserLogin;

    ~NativeUserLogin();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeUserLogin>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeUserLogin>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeUserLogin();
    friend ::djinni::JniClass<NativeUserLogin>;
    friend ::djinni::JniInterface<::UserLogin::UserLogin, NativeUserLogin>;

};

}  // namespace djinni_generated
