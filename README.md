# SingleUserOnlineSystem
单点登录系统设计方案：

整个系统分为两部分：
使用Node实现的后台svr以及使用Android实现的客户端。
前后端通信通过gRPC实现，使用RSA、md5、加盐来对数据传递进行处理；数据存储通过mysql实现。
客户端核心逻辑通过C++实现，通过DJinni提供不同平台的接口，从而实现跨平台。界面通过Android实现。

功能设计：

1.	用户注册功能。客户端使用svr的公钥加密，将密码传递给svr，svr私钥解密后存储到数据库。
2.	用户登录功能。客户端将密码与时间戳计算md5，传递给svr，svr查数据库得到密码，并通过时间戳计算md5，并与客户端传递的值进行校验。
3.	单点登录功能。用户登录后，svr在内存中保留所有用户的登录call，在用户登录时，先检查该用户是否已经登录过，如果有，则登出原有的用户，并让新的请求登录成功。
4.	按规则踢出用户。Svr端通过mysql记录规则，每分钟查询一次，将符合规则的用户踢出。


新增：

 1.新增SingleUserOnlineSvrCpp
  该项目为使用C++完成的grpc svr；
  
 2.优化了数据库中pwd的存储
 
 3.增加了bazel打包SvrCpp
 
 
 遗留问题：
 
 1.目前Android通过cmakeList完成打包，直接增量编译了grpc源码，如果系统中安装有openssl1.0.2+，则会导致boringssl无法打包进so。
    fix方法：使用grpc的so，不在使用源码编译；后面再修改
    
 2.目前SvrCpp直接使用了编译好的grpc的相关库，后面可以尝试下做个开关；控制是从grpc源码打包或是用.a库
 
 3.目前使用的是grpc的insecure连接，系统未部署在真实服务器上
 
 
 项目部署指引：

服务端：
	运行环境 MacOs 10.13.6 
	需要的软件： mysql XCode grpc protoc bazel

	运行方法：
	1.需要在mysql中建立表：
		1）用户踢出规则表
			CREATE TABLE `user_forbid` (
			  `ruleid` int(11) NOT NULL,
			  `useridrexp` varchar(45) NOT NULL,
			  PRIMARY KEY (`ruleid`,`useridrexp`)
			) ENGINE=InnoDB DEFAULT CHARSET=latin1;
		2）用户信息存储表：
			CREATE TABLE `user_info` (
			  `user_name` varchar(64) NOT NULL,
			  `user_pwd` varchar(256) NOT NULL,
			  `statue` int(11) DEFAULT '0',
			  `user_salt` varchar(32) NOT NULL,
			  PRIMARY KEY (`user_name`),
			  UNIQUE KEY `user_name_UNIQUE` (`user_name`)
			) ENGINE=InnoDB DEFAULT CHARSET=latin1;

	2. 需要在svrCpp的db_operation/SingleUserDbOperation.cpp中修改对应的数据库名、用户名及密码等
	3. 在工程根目录下执行bazel命令,即可启动svr
		bazel build //SingleUserOnlineSvrCpp:single_server
		./bazel-bin/SingleUserOnlineSvrCpp/single_server


客户端：
	编译环境 MacOs 10.13.6 
	需要的软件： Android studio(带有NDK相关工具)、djinni

	运行方法：
	1.切换到/SingleUserOnline/SingleUserOnlineClient/SingleUserOnlineApp 目录
	2.执行gradle 命令；或者通过Android studio打开工程后直接运行app
		./gradlew assembledebug
  
  
  运行指引：
  
1.需要将PC与手机接入同一个局域网。
2.修改客户端代码：
SingleUserOnline/SingleUserOnlineClient/SingleUserOnlineClient/user_login_djinni_impl.cpp
string srvaddr = "PC_IP:3001";
将PC_IP更改为PC的ip地址
3.构造apk
4.运行svrCpp程序及app
