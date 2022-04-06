load("@com_justbuchanan_rules_qt//:qt.bzl", "qt_cc_library", "qt_resource")

qt_resource(
    name = "qrc",
    files = [
        "res/grid100_w4_28o.png",
    ],
)

qt_cc_library(
    name = "widget",
    srcs = glob([
            "*.cpp",
        ],
        exclude = [
            "main.cpp"
        ]
    ),
    hdrs = glob([
            "*.h",
        ],
    ),
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_gui",
        ":qrc",
        "//graph:graph",
        ],
)

load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

cmake(
   name = "ogdf",
   lib_source = "@ogdf//:all",
   generate_args = [
       "-G Ninja",
   ],
   out_lib_dir = "lib/" + select({
       "@platforms//cpu:arm": "aarch64-linux-gnu",
       "@platforms//cpu:x86_64": "x86_64-linux-gnu",
   }),
   out_static_libs = [
       "libCOIN.a",
       "libOGDF.a",
   ],
   visibility = ["//visibility:public"]
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":widget"
    ]
)
