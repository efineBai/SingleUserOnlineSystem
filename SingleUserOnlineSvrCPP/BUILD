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
load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cc_proto_library")


cc_binary(
    name = "single_server",
    srcs = [
            "SingleUserOnlineSvrCPP/db_operation/SingleUserDbOperation.cpp",
            "SingleUserOnlineSvrCPP/SingleUserOnlineServiceImpl.cpp",
            "SingleUserOnlineSvrCPP/db_operation/SingleUserDbOperation.hpp",
            "SingleUserOnlineSvrCPP/GlobalData.hpp",
            "SingleUserOnlineSvrCPP/GlobalData.cpp",
            "SingleUserOnlineSvrCPP/tools/CommTools.hpp",
            "SingleUserOnlineSvrCPP/tools/CommTools.cpp",
            "SingleUserOnlineSvrCPP/bcrypt.c",
            "SingleUserOnlineSvrCPP/bcrypt.h",
            "SingleUserOnlineSvrCPP/crypt_blowfish/crypt.h",
            "SingleUserOnlineSvrCPP/crypt_blowfish/crypt_blowfish.c",
            "SingleUserOnlineSvrCPP/crypt_blowfish/crypt_blowfish.h",
            "SingleUserOnlineSvrCPP/crypt_blowfish/crypt_gensalt.c",
            "SingleUserOnlineSvrCPP/crypt_blowfish/crypt_gensalt.h",
            "SingleUserOnlineSvrCPP/crypt_blowfish/ow-crypt.h",
            "SingleUserOnlineSvrCPP/crypt_blowfish/wrapper.c",

            "SingleUserOnlineSvrCPP/crypt_blowfish/x86.S",
            "SingleUserOnlineSvrCPP/libmysqlclient.a",

            ],
    defines = ["BAZEL_BUILD"],
    copts = ["-I/usr/local/include",
    "-I/usr/local/include/mysql",
    "-ISingleUserOnlineSvrCPP/libbcrypt/bcrypt/",
    "-g",
   ],
   deps = ["//proto:single_user_online", "@openssl//:ssl"]
    
)


