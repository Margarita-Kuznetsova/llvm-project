#include "loveSubtarget.h"
#include "love.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define DEBUG_TYPE "love-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "loveGenSubtargetInfo.inc"

void loveSubtarget::anchor() {}

loveSubtarget::loveSubtarget(const Triple &TT, const std::string &CPU,
                             const std::string &FS, const TargetMachine &TM)
    : loveGenSubtargetInfo(TT, CPU, /*TuneCPU=*/CPU, FS), InstrInfo(*this),
      FrameLowering(*this), TLInfo(TM, *this) {}
