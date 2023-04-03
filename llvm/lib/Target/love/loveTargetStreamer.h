#ifndef LLVM_LIB_TARGET_love_loveTARGETSTREAMER_H
#define LLVM_LIB_TARGET_love_loveTARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {

class loveTargetStreamer : public MCTargetStreamer {
public:
  loveTargetStreamer(MCStreamer &S);
  ~loveTargetStreamer() override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_love_loveTARGETSTREAMER_H