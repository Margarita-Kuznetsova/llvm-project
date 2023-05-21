#include "love.h"
#include "llvm/IR/Module.h"
#include "TargetInfo/loveTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheloveTarget() {
  static Target TheloveTarget;
  return TheloveTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeloveTargetInfo() {
  RegisterTarget<Triple::love, false> X(getTheloveTarget(), "love", "love (32-bit simulator arch)", "sim");
}
