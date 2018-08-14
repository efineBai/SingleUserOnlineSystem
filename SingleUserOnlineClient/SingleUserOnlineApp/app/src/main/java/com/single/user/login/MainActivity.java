package com.single.user.login;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import javax.annotation.Nonnull;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    static {
        System.loadLibrary("native-lib");
    }
    UserLogin userLoginStub ;
    EditText userNameEdt;

    EditText userPwdEdt;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        userLoginStub = UserLogin.CppProxy.createUserInterface();
        initView();
    }

    private void initView() {
        findViewById(R.id.signup_btn).setOnClickListener(this);
        findViewById(R.id.login_btn).setOnClickListener(this);
        userNameEdt = (EditText)findViewById(R.id.username_edt);
        userPwdEdt = (EditText)findViewById(R.id.userpwd_edt);
    }

    @Override
    public void onClick(View v) {
        if(TextUtils.isEmpty(userNameEdt.getText().toString())
            || TextUtils.isEmpty(userPwdEdt.getText().toString())){
            Toast.makeText(this, "用户名和密码不能为空", Toast.LENGTH_LONG).show();
            return;
        }
        String userName = userNameEdt.getText().toString();
        String userPwd = userPwdEdt.getText().toString();
        switch (v.getId()){
            case R.id.signup_btn:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        userLoginStub.signUp(userName, userPwd, loginStatusCallback);
                    }
                }).start();

                break;
            case R.id.login_btn:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        userLoginStub.login(userName, userPwd, loginStatusCallback);
                    }
                }).start();
                break;
                default:

        }
    }

    final  LoginStatusCallback loginStatusCallback = new LoginStatusCallback() {
        @Override
        public void onLoginSucc() {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Log.d("LoginSucc", "登录成功：");
                    Toast.makeText(MainActivity.this, "登录成功", Toast.LENGTH_LONG).show();
                }
            });
        }

        @Override
        public void onLoginOut(int retCode, @Nonnull String msg) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Log.d("LoginFailed", "登出成功：");
                    Toast.makeText(MainActivity.this, "用户登出成功："+"ret="+retCode+" | msg="+msg, Toast.LENGTH_LONG).show();
                }
            });
        }

        @Override
        public void onLoginFailed(int retCode, @Nonnull String msg) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Log.d("LoginFailed", "用户登录失败："+"ret="+retCode+" | msg="+msg);
                    Toast.makeText(MainActivity.this, "用户登录失败："+"ret="+retCode+" | msg="+msg, Toast.LENGTH_LONG).show();
                }
            });
        }

        @Override
        public void onSignUpSucc() {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Log.d("LoginSucc", "用户注册成功：");
                    Toast.makeText(MainActivity.this, "用户注册成功", Toast.LENGTH_LONG).show();
                }
            });
        }

        @Override
        public void onSignUpFailed(int retCode, @Nonnull String msg) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Log.d("LoginFailed", "用户注册失败：");
                    Toast.makeText(MainActivity.this, "用户注册失败："+"ret="+retCode+" | msg="+msg, Toast.LENGTH_LONG).show();
                }
            });
        }
    };


}
