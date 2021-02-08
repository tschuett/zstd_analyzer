#pragma once

#include "DataExtractor.h"

namespace Zstandard {

class ZstandardFrame {
  DataExtractor extractor;
  uint64_t blockMaximumSize;
  uint8_t contentChecksumFlag;
public:
  ZstandardFrame(DataExtractor extractor) : extractor(extractor){};

  void run();

public:
  void runOnFrameHeader();
  void runOnBlocks();

  void runOnSkippleFrame();

};

} // namespace Zstandard
