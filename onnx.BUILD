load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
    name = "onnx_proto",
    srcs = ["onnx/onnx-ml.proto"],
)

cc_proto_library(
    name = "onnx_cc_proto",
    deps = [":onnx_proto"],
)

cc_library(
    name = "onnx",
    hdrs = ["onnx/onnx_pb.h"],
    defines = [
        "ONNX_ML",
        "ONNX_NAMESPACE=onnx"
    ],
    deps = [
        ":onnx_cc_proto"
    ],
    visibility = ["//visibility:public"],
)
