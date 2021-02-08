#include "ZstandardBlock.h"

#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

#include <algorithm>

namespace Zstandard {

bool ZstandardBlock::run() {
  uint32_t blockHeader = extractor.getUnsigned(3);

  uint8_t lastBlock = blockHeader & 0b01;
  uint8_t blockType = (blockHeader >> 1) & 0b011;
  uint32_t blockSize = (blockHeader >> 3);

  uint64_t blockContentSize = 0;
  switch (blockType) {
    case 0:
      blockContentSize = blockSize;
      break;
    case 1:
      blockContentSize = 1;
      break;
    case 2:
      blockContentSize = blockSize;
      break;
    case 3:
      llvm_unreachable("unknown block type");
  }

  blockContentSize = std::min(blockContentSize, blockMaximumSize);

  llvm::outs() << " block: " << blockContentSize << '\n';

  extractor.skip(blockContentSize);

  return lastBlock == 0;
}

} // namespace Zstandard
