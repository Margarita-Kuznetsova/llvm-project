//===-- LOVE.h - Top-level interface for LOVE representation ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM LOVE back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_LOVE_LOVE_H
#define LLVM_LIB_TARGET_LOVE_LOVE_H

#include "MCTargetDesc/LOVEMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class LOVETargetMachine;
  class FunctionPass;

} // end namespace llvm;

#endif
