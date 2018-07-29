// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from UserLogin.djinni

#include "NativeUserLogin.hpp"  // my header
#include "Marshal.hpp"
#include "NativeLoginStatusCallback.hpp"

namespace djinni_generated {

NativeUserLogin::NativeUserLogin() : ::djinni::JniInterface<::UserLogin::UserLogin, NativeUserLogin>("com/single/user/login/UserLogin$CppProxy") {}

NativeUserLogin::~NativeUserLogin() = default;


CJNIEXPORT void JNICALL Java_com_single_user_login_UserLogin_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::UserLogin::UserLogin>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jint JNICALL Java_com_single_user_login_UserLogin_00024CppProxy_native_1signUp(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_userName, jstring j_pwd, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::UserLogin::UserLogin>(nativeRef);
        auto r = ref->sign_up(::djinni::String::toCpp(jniEnv, j_userName),
                              ::djinni::String::toCpp(jniEnv, j_pwd),
                              ::djinni_generated::NativeLoginStatusCallback::toCpp(jniEnv, j_callback));
        return ::djinni::release(::djinni::I32::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jint JNICALL Java_com_single_user_login_UserLogin_00024CppProxy_native_1login(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_userName, jstring j_pwd, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::UserLogin::UserLogin>(nativeRef);
        auto r = ref->login(::djinni::String::toCpp(jniEnv, j_userName),
                            ::djinni::String::toCpp(jniEnv, j_pwd),
                            ::djinni_generated::NativeLoginStatusCallback::toCpp(jniEnv, j_callback));
        return ::djinni::release(::djinni::I32::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jint JNICALL Java_com_single_user_login_UserLogin_00024CppProxy_native_1logout(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_userName, jstring j_pwd, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::UserLogin::UserLogin>(nativeRef);
        auto r = ref->logout(::djinni::String::toCpp(jniEnv, j_userName),
                             ::djinni::String::toCpp(jniEnv, j_pwd),
                             ::djinni_generated::NativeLoginStatusCallback::toCpp(jniEnv, j_callback));
        return ::djinni::release(::djinni::I32::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

}  // namespace djinni_generated
