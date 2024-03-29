// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from UserLogin.djinni

package com.single.user.login;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class LoginStatusCallback {
    public abstract void onLoginSucc();

    public abstract void onLoginOut();

    public abstract void onLoginFailed();

    private static final class CppProxy extends LoginStatusCallback
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
        public void onLoginSucc()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_onLoginSucc(this.nativeRef);
        }
        private native void native_onLoginSucc(long _nativeRef);

        @Override
        public void onLoginOut()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_onLoginOut(this.nativeRef);
        }
        private native void native_onLoginOut(long _nativeRef);

        @Override
        public void onLoginFailed()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_onLoginFailed(this.nativeRef);
        }
        private native void native_onLoginFailed(long _nativeRef);
    }
}
