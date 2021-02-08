load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//:variables.bzl", "CXXOPTS", "LOPTS")

package(
    features=["layering_check"],
    licenses=["notice"],
)

cc_library(
    name="Zstandard",
    srcs=[
        "Zstandardfile.cpp",
        "ZstandardFrame.cpp",
        "ZstandardFrame.h",
        "ZstandardBlock.cpp",
        "ZstandardBlock.h",
        "DataExtractor.cpp",
    ],
    visibility=["//:__pkg__"],
    hdrs=[
        "ZstandardFile.h",
        "DataExtractor.h",
    ],
    copts=CXXOPTS,
    deps=[
        "@llvm-project//llvm:Support",
    ],
)
