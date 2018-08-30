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


package(default_visibility = ["//visibility:public"])

# load("@org_pubref_rules_protobuf//closure:rules.bzl", "closure_proto_library")
load("//cpp:rules.bzl", "cc_proto_library")

filegroup(
  name = 'protos',
  srcs = [
    "protos/single_user_online.proto"
  ],
)

cc_proto_library(
  name = "single_user_online",
  protos = [":protos"],
  verbose = 2, # 0=no output, 1=show protoc command, 2+ more...
)

cc_binary(
    name = "single_server",
    srcs = [
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/db_operation/SingleUserDbOperation.cpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/SingleUserOnlineServiceImpl.cpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/db_operation/SingleUserDbOperation.hpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/GlobalData.hpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/GlobalData.cpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/tools/CommTools.hpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/tools/CommTools.cpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/bcrypt.c",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/bcrypt.h",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/crypt_blowfish/crypt.h",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/crypt_blowfish/crypt_blowfish.c",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/crypt_blowfish/crypt_blowfish.h",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/crypt_blowfish/crypt_gensalt.c",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/crypt_blowfish/crypt_gensalt.h",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/crypt_blowfish/ow-crypt.h",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/crypt_blowfish/wrapper.c",

            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/crypt_blowfish/x86.S",
            "SingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libmysqlclient.a",

            ],
    defines = ["BAZEL_BUILD"],
    copts = ["-I/usr/local/include",
    "-I/usr/local/include/mysql",
    "-ISingleUserOnlineSvrCPP/SingleUserOnlineSvrCPP/libbcrypt/bcrypt/",
   ],
   deps = [":single_user_online", "@openssl//:ssl"]
    
)


