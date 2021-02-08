#pragma once

#include "DataExtractor.h"

namespace Zstandard {

class ZstandardFile {
  DataExtractor extractor;

public:
  ZstandardFile(int fd) : extractor(fd){};

  void run();
};

} // namespace Zstandard
