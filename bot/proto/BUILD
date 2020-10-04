load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
    name = "log_proto",
    srcs = ["log.proto"],
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "log_cc_proto",
    deps = [":log_proto"],
    visibility = ["//visibility:public"],
)
