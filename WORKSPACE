workspace(name="SingleOnlineUserSvrCPP")

local_repository(
  name = "org_pubref_rules_protobuf",
  #remote = "https://github.com/pubref/rules_protobuf.git",
  #tag = "v0.8.2",
  #commit = "5cae42382b620aa1e347ecf30b3e92fd0d97998c" # alternatively, use latest commit on master
  path = "deps/rules_protobuf"
)

load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cpp_proto_repositories")

cpp_proto_repositories()

load("@org_pubref_rules_protobuf//protobuf:rules.bzl", "github_archive")
github_archive(
    name = "io_bazel_rules_go",
    commit = "f676870c5caf8df559a51e7aa005d2ece148a03b",  # 0.10.3
    org = "bazelbuild",
    repo = "rules_go",
    sha256 = "d1740b1a75d3c51f1c37e5a42ed032d113bdf1de35c393c609940af491ab6035",
)

load("@io_bazel_rules_go//go:def.bzl", "go_rules_dependencies", "go_register_toolchains")

go_rules_dependencies()

go_register_toolchains()


load("@org_pubref_rules_protobuf//protobuf:rules.bzl", "proto_repositories")
proto_repositories()

load("@org_pubref_rules_protobuf//grpc_gateway:rules.bzl", "grpc_gateway_proto_repositories")
grpc_gateway_proto_repositories()