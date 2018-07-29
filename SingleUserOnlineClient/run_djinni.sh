#!/bin/sh

#  djinni_run.sh
#  SingleUserOnlineClient
#
#  Created by castlebai on 26/7/2018.
#  Copyright © 2018 castlebai. All rights reserved.

# Locate the script file.  Cross symlinks if necessary.
base_dir=$(cd "`dirname "0"`" && pwd)
cpp_out="$base_dir/generated-src/cpp"
jni_out="$base_dir/generated-src/jni"
objc_out="$base_dir/generated-src/objc"
java_out="$base_dir/generated-src/java/com/single/user/login"
java_package="com.single.user.login"
namespace="UserLogin"
objc_prefix="UserLogin_"
djinni_file="UserLogin.djinni"

deps/djinni/src/run-assume-built \
--java-out $java_out \
--java-package $java_package \
--ident-java-field mFooBar \
\
--cpp-out $cpp_out \
--cpp-namespace $namespace \
\
--jni-out $jni_out \
--ident-jni-class NativeFooBar \
--ident-jni-file NativeFooBar \
\
--objc-out $objc_out \
--objc-type-prefix $objc_prefix \
\
--objcpp-out $objc_out \
\
--idl $djinni_file
