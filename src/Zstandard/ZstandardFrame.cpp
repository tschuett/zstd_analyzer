#include "ZstandardFrame.h"

#include "ZstandardBlock.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "llvm/Support/raw_ostream.h"

#include <algorithm>
#include <optional>

namespace Zstandard {

void ZstandardFrame::run() {
  uint32_t magicNumber = extractor.getU32();

  if (magicNumber == 0xFD2FB528) {
    runOnFrameHeader();
    runOnBlocks();
    if (contentChecksumFlag) {
      [[maybe_unused]] uint32_t checkSum = extractor.getU32();
    }
  } else if ((magicNumber >> 4) == 0x184D2A5) {
    runOnSkippleFrame();
  } else {
    printf("didn't find magic number\n");
    exit(EXIT_FAILURE);
  }
}

void ZstandardFrame::runOnSkippleFrame() {
  uint32_t frameSize = extractor.getU32();

  llvm::outs() << "skippable frame: " << frameSize << '\n';

  extractor.skip(frameSize);
}

void ZstandardFrame::runOnFrameHeader() {
  uint8_t frameHeaderDescriptor = extractor.getU8();

  uint8_t frameContentSizeFlag = (frameHeaderDescriptor >> 6) & 0b11;
  uint8_t singleSegmentFlag = (frameHeaderDescriptor >> 5) & 0b01;

  uint8_t frameContentFieldSize = 0;
  if (frameContentSizeFlag == 0) {
    if (singleSegmentFlag == 0)
      frameContentFieldSize = 0;
    else
      frameContentFieldSize = 1;
  } else if (frameContentSizeFlag == 1)
    frameContentFieldSize = 2;
  else if (frameContentSizeFlag == 2)
    frameContentFieldSize = 4;
  else if (frameContentSizeFlag == 3)
    frameContentFieldSize = 8;

  contentChecksumFlag = (frameHeaderDescriptor >> 2) & 0b11;

  uint8_t dictionaryIdFlag = (frameHeaderDescriptor >> 0) & 0b11;

  std::optional<uint64_t> windowSize;
  if (singleSegmentFlag == 0) {
    uint8_t windowDescriptor = extractor.getU8();
    uint8_t mantissa = windowDescriptor & 0b011;
    uint8_t exponent = (windowDescriptor >> 3) & 0b11111;
    uint64_t windowLog = 10 + exponent;
    uint64_t windowBase = 1 << windowLog;
    uint64_t windowAdd = (windowBase / 8) * mantissa;
    windowSize = windowBase + windowAdd;
  }

  [[maybe_unused]] uint64_t dictionaryId =
      extractor.getUnsigned(dictionaryIdFlag);

  uint64_t frameContentSize = extractor.getUnsigned(frameContentFieldSize);
  if (frameContentFieldSize == 2)
    frameContentSize += 256;

  [[maybe_unused]] uint32_t sizeOfWindowDescriptor =
      singleSegmentFlag == 1 ? 0 : 1;
  [[maybe_unused]] uint32_t sizeOfDictionaryId = dictionaryIdFlag;

  printf("frame\n");
  if (frameContentFieldSize not_eq 0) {
    llvm::outs() << " frameContentSize: " << frameContentSize << '\n';
  } else {
    if (windowSize)
      llvm::outs() << " windowSize: " << windowSize.value() << '\n';
  }

  if (windowSize)
    blockMaximumSize =
        std::min(windowSize.value(), (uint64_t)128 * 1024 * 1024);
  else
    blockMaximumSize = 128 * 1024 * 1024;
}

void ZstandardFrame::runOnBlocks() {

  bool continueBlocks = false;
  do {
    ZstandardBlock block = {extractor, blockMaximumSize};

    continueBlocks = block.run();

  } while (continueBlocks);
}

} // namespace Zstandard
