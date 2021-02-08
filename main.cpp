#include "src/Zstandard/ZstandardFile.h"
#include "zstd.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "llvm/Support/xxhash.h"

#include <cstdio>
#include <cstdlib>
#include <string>

int main(int argc, char **argv) {

  int fd = open(file.c_str(), O_RDONLY);

  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  Zstandard::ZstandardFile zfile = {fd};

  zfile.run();
  printf("zstd version: %u\n", ZSTD_versionNumber());

  return 0;
}
