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



cc_binary(
    name = "single_server",
    srcs = [
            "SingleUserOnlineSvrCPP/db_operation/SingleUserDbOperation.cpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineServiceImpl.cpp",
            "SingleUserOnlineSvrCPP/single_user_online.grpc.pb.h",
            "SingleUserOnlineSvrCPP/single_user_online.pb.h",
            "SingleUserOnlineSvrCPP/db_operation/SingleUserDbOperation.hpp",
            "SingleUserOnlineSvrCPP/grpc_gen/single_user_online.grpc.pb.cc",
            "SingleUserOnlineSvrCPP/grpc_gen/single_user_online.grpc.pb.h",
            "SingleUserOnlineSvrCPP/grpc_gen/single_user_online.pb.cc",
            "SingleUserOnlineSvrCPP/grpc_gen/single_user_online.pb.h",
            "SingleUserOnlineSvrCPP/GlobalData.hpp",
            "SingleUserOnlineSvrCPP/GlobalData.cpp",
            "SingleUserOnlineSvrCPP/tools/CommTools.hpp",
            "SingleUserOnlineSvrCPP/tools/CommTools.cpp",
            "SingleUserOnlineSvrCPP/libgrpc++_reflection.a",
            "SingleUserOnlineSvrCPP/libgrpc++.a",
            "SingleUserOnlineSvrCPP/libgrpc++_unsecure.a",
            "SingleUserOnlineSvrCPP/libmysqlclient.a",
            "SingleUserOnlineSvrCPP/libgpr.a",
            "SingleUserOnlineSvrCPP/libgrpc.a",
            "SingleUserOnlineSvrCPP/libgflags.a",
            "SingleUserOnlineSvrCPP/libcrypto.a",
            "SingleUserOnlineSvrCPP/libssl.a",
            "SingleUserOnlineSvrCPP/libgrpc_cronet.a",
            "SingleUserOnlineSvrCPP/libgrpc_plugin_support.a",
            "SingleUserOnlineSvrCPP/libgrpc_unsecure.a",
            "SingleUserOnlineSvrCPP/libgrpc++_core_stats.a",
            "SingleUserOnlineSvrCPP/libgrpc++_cronet.a",
            "SingleUserOnlineSvrCPP/libgrpc++_error_details.a",
            "SingleUserOnlineSvrCPP/libgrpcpp_channelz.a",
            "SingleUserOnlineSvrCPP/libares.a",
            "SingleUserOnlineSvrCPP/libprotobuf.a",
            ],
    defines = ["BAZEL_BUILD"],
    copts = ["-I/usr/local/include",
    "-I/usr/local/include/mysql",
   ],
    
)


