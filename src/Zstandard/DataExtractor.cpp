#include "DataExtractor.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "llvm/Support/ErrorHandling.h"

#include <cstdint>

namespace Zstandard {

uint8_t DataExtractor::getU8() const {
  uint8_t value;

  ssize_t size = read(fd, &value, sizeof(value));
  if (size not_eq sizeof(value)) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  return value;
}

uint16_t DataExtractor::getU16() const {
  uint16_t value;

  ssize_t size = read(fd, &value, sizeof(value));
  if (size not_eq sizeof(value)) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  return value;
}

uint32_t DataExtractor::getU24() const {
  uint32_t firstTwoBytes = getU16();
  uint32_t lastByte = getU8();

  return firstTwoBytes + (lastByte << 16);
}

uint32_t DataExtractor::getU32() const {
  uint32_t value;

  ssize_t size = read(fd, &value, sizeof(value));
  if (size not_eq sizeof(value)) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  return value;
}

uint64_t DataExtractor::getU64() const {
  uint64_t value;

  ssize_t size = read(fd, &value, sizeof(value));
  if (size not_eq sizeof(value)) {
    perror("read");
    exit(EXIT_FAILURE);
  }

  return value;
}

uint64_t DataExtractor::getUnsigned(uint32_t size) const {
  switch (size) {
    case 0:
      return 0xDEADBEEF;
    case 1:
      return getU8();
    case 2:
      return getU16();
    case 3:
      return getU24();
    case 4:
      return getU32();
    case 8:
      return getU64();
  }
  printf("%u\n", size);
  llvm_unreachable("getUnsigned unhandled case!");
}

void DataExtractor::skip(uint64_t bytes) const {

  off_t offset = lseek(fd, bytes, SEEK_CUR);

  if (offset == -1) {
    perror("lseek");
    exit(EXIT_FAILURE);
  }
}

bool DataExtractor::eof() const {
  off_t currentPosition = lseek(fd, 0, SEEK_CUR);
  if (currentPosition == -1) {
    perror("lseek");
    exit(EXIT_FAILURE);
  }
  off_t endPosition = lseek(fd, 0, SEEK_END);
  if (endPosition == -1) {
    perror("lseek");
    exit(EXIT_FAILURE);
  }
  bool isEof = currentPosition == endPosition;
  currentPosition = lseek(fd, currentPosition, SEEK_SET);
  if (currentPosition == -1) {
    perror("lseek");
    exit(EXIT_FAILURE);
  }

  return isEof;
}

} // namespace Zstandard
