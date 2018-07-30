// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from UserLogin.djinni

package com.single.user.login;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class UserLogin {
    public abstract int signUp(String userName, String pwd, LoginStatusCallback callback);

    public abstract int login(String userName, String pwd, LoginStatusCallback callback);

    private static final class CppProxy extends UserLogin
    {
        private final long nativeRef;
        private final AtomicBoolean destroyed = new AtomicBoolean(false);

        private CppProxy(long nativeRef)
        {
            if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
            this.nativeRef = nativeRef;
        }

        private native void nativeDestroy(long nativeRef);
        public void _djinni_private_destroy()
        {
            boolean destroyed = this.destroyed.getAndSet(true);
            if (!destroyed) nativeDestroy(this.nativeRef);
        }
        protected void finalize() throws java.lang.Throwable
        {
            _djinni_private_destroy();
            super.finalize();
        }

        @Override
        public int signUp(String userName, String pwd, LoginStatusCallback callback)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_signUp(this.nativeRef, userName, pwd, callback);
        }
        private native int native_signUp(long _nativeRef, String userName, String pwd, LoginStatusCallback callback);

        @Override
        public int login(String userName, String pwd, LoginStatusCallback callback)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_login(this.nativeRef, userName, pwd, callback);
        }
        private native int native_login(long _nativeRef, String userName, String pwd, LoginStatusCallback callback);
    }
}