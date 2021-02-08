# zstd_analyzer



> {repeat 10000 echo some test} > large-file
> zstd large-file
> > bazel run zstd_analyzer


https://github.com/facebook/zstd/blob/dev/doc/zstd_compression_format.md
