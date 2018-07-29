cmake_minimum_required(VERSION 3.4.1)
# grpc 需要 c++11
add_compile_options(-std=c++11)
# 添加grpc,protobuff的库的位置


#find_package(GRPC REQUIRED)
#find_package(Protobuf REQUIRED)


# 定义要参与编译的 C++ 文件
file(GLOB SOURCES
    src/main/cpp/src/*.cpp
    src/main/cpp/src/*.h
    ../../generated-src/cpp/*.cpp
    ../../generated-src/jni/*.cpp
    ../../deps/djinni/support-lib/jni/*.cpp
    ../../SingleUserOnlineClient/*.cpp
    )

# 将上述文件编译一个名为 `native-lib` 的 so
add_library(native-lib
            SHARED
            ${SOURCES} )

# C++ 头文件的搜索路径
include_directories(
   /usr/local/include
   src/main/cpp/src/*.hpp
   src/main/cpp/src/*.h
   ../../deps/djinni/support-lib
   ../../deps/djinni/support-lib/jni
   ../../generated-src/cpp
   ../../generated-src/jni
   ../../SingleUserOnlineClient/*.hpp
   ../../SingleUserOnlineClient/*.h
   ../../deps/grpc/include
)
#添加链接库




 # NDK 提供了一些基础库，比如这里查找 log 这个库的路径，保存到 log-lib 这个变量里
 find_library(log-lib log)
 #find_library(grpc grpc++_reflection)
 #find_library(proto protobuf)

    message( STATUS ------------------------)
    message( STATUS ${log-lib} )
    message( STATUS ${protobuf} )
    message( STATUS ${grpc++} )
    message( STATUS ${grpc} )
    message( STATUS ${grpc_cronet} )
    message( STATUS ${grpc++_core_stats} )
    message( STATUS ------------------------)




# 将我们的 so 和这个 log 这个库链接
target_link_libraries(native-lib
                    ${log-lib}
                    )
