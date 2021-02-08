workspace(name="zstd-analyzer")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# c/c++
http_archive(
    name="rules_cc",
    sha256="9a446e9dd9c1bb180c86977a8dc1e9e659550ae732ae58bd2e8fd51e15b2c91d",
    urls=["https://github.com/bazelbuild/rules_cc/archive/262ebec3c2296296526740db4aefce68c80de7fa.zip"],
    strip_prefix="rules_cc-262ebec3c2296296526740db4aefce68c80de7fa",
)

# zstd
http_archive(
    name="com_github_cschuet_zstd",
    sha256="a17d4591605bdbffc2ce3cffd4edbd6a5412c308ee6322d90b91cc4f670071cc",
    strip_prefix="zstd-1-0790403a9c2d1f512d012294f304a6bfe97f7487",
    urls=[
        "https://github.com/yasushi-saito/zstd-1/archive/0790403a9c2d1f512d012294f304a6bfe97f7487.tar.gz",
    ],
)

load("@com_github_cschuet_zstd//bazel:repositories.bzl", "repositories")

repositories()

# LLVM
LLVM_COMMIT = "499bce3abab8a362b9b4197944bd40b826c736c4"

LLVM_BAZEL_TAG = "llvm-project-%s" % (LLVM_COMMIT,)

LLVM_BAZEL_SHA256 = "a05a83300b6b4d8b45c9ba48296c06217f3ea27ed06b7e698896b5a3b2ed498d"

http_archive(
    name = "llvm-bazel",
    sha256 = LLVM_BAZEL_SHA256,
    strip_prefix = "llvm-bazel-{tag}/llvm-bazel".format(tag = LLVM_BAZEL_TAG),
    url = "https://github.com/google/llvm-bazel/archive/{tag}.tar.gz".format(tag = LLVM_BAZEL_TAG),
)

LLVM_SHA256 = "a154965dfeb2b5963acc2193bc334ce90b314acbe48430ba310d8a7c7a20de8b"

LLVM_URLS = [
    "https://storage.googleapis.com/mirror.tensorflow.org/github.com/llvm/llvm-project/archive/{commit}.tar.gz".format(commit = LLVM_COMMIT),
    "https://github.com/llvm/llvm-project/archive/{commit}.tar.gz".format(commit = LLVM_COMMIT),
]

http_archive(
    name = "llvm-project-raw",
    build_file_content = "#empty",
    sha256 = LLVM_SHA256,
    strip_prefix = "llvm-project-" + LLVM_COMMIT,
    urls = LLVM_URLS,
)

load("@llvm-bazel//:terminfo.bzl", "llvm_terminfo_disable")

llvm_terminfo_disable(
    name = "llvm_terminfo",
)

load("@llvm-bazel//:zlib.bzl", "llvm_zlib_disable")

llvm_zlib_disable(
    name = "llvm_zlib",
)

load("@llvm-bazel//:configure.bzl", "llvm_configure")

llvm_configure(
    name = "llvm-project",
    src_path = ".",
    src_workspace = "@llvm-project-raw//:WORKSPACE",
)
