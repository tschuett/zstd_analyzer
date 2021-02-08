#include "ZstandardFile.h"

#include "ZstandardFrame.h"

#include "llvm/Support/MemoryBuffer.h"

#include <memory>

namespace Zstandard {

void ZstandardFile::run() {

  while (not extractor.eof()) {
    ZstandardFrame frame = {extractor};
    frame.run();
  }
}

} // namespace Zstandard
