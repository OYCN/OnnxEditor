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

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":widget"
    ]
)
