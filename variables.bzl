DARWIN_CXX_OPTS = [
    "-Wall",
    "-Werror",
    "-pedantic",
    "-std=c++17",
    "-O3",
    "-march=native",
    "-mtune=skylake",
    "-g0",
    "-glldb",
]

GCC_CXX_OPTS = [
    "-Wall",
    "-Werror",
    "-pedantic",
    "-std=c++17",
    "-O3",
    "-march=native",
    "-mtune=skylake",
    "-g0",
    "-ggdb",
]

COPTS = [
    "-Wall",
    "-Werror",
    "-pedantic",
    "-std=c17",
    "-O3",
    "-march=native",
    "-mtune=skylake",
    "-g0",
    "-glldb",
]

LOPTS = [
    "-O3",
]

CXXOPTS = select({
    "@platforms//os:macos": DARWIN_CXX_OPTS,
    "//conditions:default": GCC_CXX_OPTS,
})
