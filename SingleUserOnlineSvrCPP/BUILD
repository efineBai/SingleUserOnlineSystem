# Copyright 2017 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])  # 3-clause BSD

package(default_visibility = ["//visibility:public"])

load("//bazel:grpc_build_system.bzl", "grpc_proto_library")

grpc_proto_library(
    name = "auth_sample",
    srcs = ["protos/auth_sample.proto"],
)

grpc_proto_library(
    name = "hellostreamingworld",
    srcs = ["protos/hellostreamingworld.proto"],
)

grpc_proto_library(
    name = "helloworld",
    srcs = ["protos/helloworld.proto"],
)

grpc_proto_library(
    name = "route_guide",
    srcs = ["protos/route_guide.proto"],
)

grpc_proto_library(
    name = "single_user_online",
    srcs = ["protos/single_user_online.proto"],
)

cc_binary(
    name = "greeter_client",
    srcs = ["cpp/helloworld/greeter_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [":helloworld", "//:grpc++"],
)

cc_binary(
    name = "greeter_server",
    srcs = ["cpp/helloworld/greeter_server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [":helloworld", "//:grpc++"],
)


cc_binary(
    name = "single_server",
    srcs = [
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/db_operation/SingleUserDbOperation.cpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/SingleUserOnlineServiceImpl.cpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/single_user_online.grpc.pb.h",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/single_user_online.pb.h",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/db_operation/SingleUserDbOperation.hpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/GlobalData.hpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/tools/CommTools.hpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/tools/CommTools.cpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc++_reflection.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc++.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc++_unsecure.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libmysqlclient.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgpr.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgflags.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libcrypto.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libssl.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc_cronet.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc_plugin_support.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc_unsecure.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc++_core_stats.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc++_cronet.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpc++_error_details.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libgrpcpp_channelz.a",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libares.a",
            ],
    defines = ["BAZEL_BUILD"],
    copts = ["-I/usr/local/include",
    "-I/usr/local/include/mysql",
   ],
    deps = [":single_user_online"],
)


