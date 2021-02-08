#pragma once

#include <cstdint>

namespace Zstandard {

class DataExtractor {
  int fd;

public:
  DataExtractor(int fd) : fd(fd){};

  uint8_t getU8() const;
  uint16_t getU16() const;
  uint32_t getU24() const;
  uint32_t getU32() const;
  uint64_t getU64() const;
  uint64_t getUnsigned(uint32_t size) const;

  void skip(uint64_t bytes) const;

  bool eof() const;
};

} // namespace Zstandard
