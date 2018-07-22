cmake_minimum_required(VERSION 3.10)
project(SingleUserOnlineClient)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(SingleUserOnlineClient)

add_executable(SingleUserOnlineClient
        SingleUserOnlineClient/single_user_online_client.cpp
        SingleUserOnlineClient/single_user_online_client.hpp
        SingleUserOnlineClient/main.cpp
        single_user_online.pb.cc
        single_user_online.pb.h)
