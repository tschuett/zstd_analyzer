#pragma once

#include "DataExtractor.h"

namespace Zstandard {

class ZstandardBlock {
  DataExtractor extractor;
  uint64_t blockMaximumSize;
  enum class BlockType { RawBlock, RLEBlock, CompressedBlock, Reserved };

public:
  ZstandardBlock(DataExtractor extractor, uint64_t blockMaximumSize)
      : extractor(extractor), blockMaximumSize(blockMaximumSize){};

  bool run();
};

} // namespace Zstandard
