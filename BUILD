load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//:variables.bzl", "CXXOPTS", "LOPTS")

package(
    features=["layering_check"],
    licenses=["notice"],
)

cc_binary(
    name="zstd_analyzer",
    linkopts=LOPTS,
    deps=[
        ":libzstdanalyzer",
    ],
)

cc_library(
    name="libzstdanalyzer",
    srcs=[
        "main.cpp",
    ],
    hdrs=[
    ],
    copts=CXXOPTS,
    deps=[
        "@com_github_facebook_zstd//:libzstd",
        "@llvm-project//llvm:Support",
        "//src/Zstandard",
    ],
)
