#include "src/Zstandard/ZstandardFile.h"
#include "zstd.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "llvm/Support/Path.h"
#include "llvm/Support/xxhash.h"

#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {

  if (argc not_eq 2) {
    printf("zstd_analyzer <file>\n");
    exit(EXIT_FAILURE);
  }

  if (not llvm::sys::path::is_absolute(argv[1])) {
      printf("need to provide an absolute path\n");
      exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDONLY);

  if (fd == -1) {
    printf("%s\n", argv[1]);
    perror("open");
    exit(EXIT_FAILURE);
  }

  Zstandard::ZstandardFile zfile = {fd};

  zfile.run();
  printf("zstd version: %u\n", ZSTD_versionNumber());

  return 0;
}
