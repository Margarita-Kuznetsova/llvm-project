//===-- LOVETargetInfo.cpp - LOVE Target Implementation -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "LOVE.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target llvm::TheLOVETarget;

extern "C" void LLVMInitializeLOVETargetInfo() {
  RegisterTarget<Triple::LOVE,
                 /*HasJIT=*/false>
      X(TheLOVETarget, "LOVE", "LOVE (32-bit LOVEulator arch)", "LOVE");
}
