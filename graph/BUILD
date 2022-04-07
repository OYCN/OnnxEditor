load("@com_justbuchanan_rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
    name = "graph",
    srcs = glob([
            "*.cpp",
        ],
    ),
    hdrs = glob([
            "*.hpp",
        ],
    ),
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_gui",
        "//layout:layout",
        ],
    visibility = ["//visibility:public"],
)
