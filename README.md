# zstd_analyzer


```shell
> {repeat 10000 echo some test} > large-file

> zstd large-file

> bazel run :zstd_analyzer -- `pwd`/large-file.zst
```

Note that the filename has to be an absolute path.


[Zstandard Compression Format](https://github.com/facebook/zstd/blob/dev/doc/zstd_compression_format.md)



```shell
> wget wget https://github.com/llvm/llvm-project/archive/499bce3abab8a362b9b4197944bd40b826c736c4.tar.gz
> gunzip 499bce3abab8a362b9b4197944bd40b826c736c4.tar.gz
> zstd 499bce3abab8a362b9b4197944bd40b826c736c4.tar
> bazel run :zstd_analyzer -- /Users/schuett/Work/zstd_analyzer/499bce3abab8a362b9b4197944bd40b826c736c4.tar.zst
```
