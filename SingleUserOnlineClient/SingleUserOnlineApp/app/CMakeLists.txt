cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(GRPC_SRC_DIR ../../../deps/grpc)

set(GRPC_BUILD_DIR ../grpc/outputs/${ANDROID_ABI})
file(MAKE_DIRECTORY ${GRPC_BUILD_DIR})

add_subdirectory(${GRPC_SRC_DIR} ${GRPC_BUILD_DIR})

set(GRPC_PROTO_GENS_DIR ../proto-src)
file(MAKE_DIRECTORY ${GRPC_PROTO_GENS_DIR})
include_directories(${GRPC_PROTO_GENS_DIR})

set(RELFIL_WE single_user_online)
list(APPEND HELLOWORLD_PROTO_SRCS "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.pb.cc")
list(APPEND HELLOWORLD_PROTO_HDRS "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.pb.h")
list(APPEND HELLOWORLD_PROTO_SRCS "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.grpc.pb.cc")
list(APPEND HELLOWORLD_PROTO_HDRS "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.grpc.pb.h")

 add_library(helloworld_proto_lib SHARED ${HELLOWORLD_PROTO_HDRS} ${HELLOWORLD_PROTO_SRCS})

  MESSAGE( STATUS "list header =${HELLOWORLD_PROTO_HDRS}")

target_link_libraries(helloworld_proto_lib
  grpc++
  libprotobuf
  android
  log)

find_library(log-lib
 log)
# 定义要参与编译的 C++ 文件
file(GLOB SOURCES
    src/main/cpp/src/*.cpp
    src/main/cpp/src/*.h
    ../../SingleUserOnlineClient/*.hpp
    ../../SingleUserOnlineClient/*.cpp
    ../../SingleUserOnlineClient/*.h
    ../../SingleUserOnlineClient/*.c
    ../../generated-src/cpp/*.hpp
    ../../generated-src/jni/*.cpp
    ../../SingleUserOnlineClient/crypt_blowfish/*.h
    ../../SingleUserOnlineClient/crypt_blowfish/*.c
    ../../SingleUserOnlineClient/crypt_blowfish/*.S
    ../../deps/djinni/support-lib/jni/*.cpp
    )
include_directories(
    ../../../deps/grpc/third_party/boringssl/include
    ../../SingleUserOnlineClient/crypt_blowfish
    ../../deps/djinni/support-lib/jni
    ../../generated-src/cpp
    ../../generated-src/jni
    ../../SingleUserOnlineClient
)
# 将上述文件编译一个名为 `native-lib` 的 so
add_library(native-lib
            SHARED
            ${SOURCES} )


target_include_directories(native-lib
  PRIVATE ${HELLOWORLD_PROTO_HEADERS})

target_link_libraries(native-lib
  helloworld_proto_lib
  android
  ${log-lib})
