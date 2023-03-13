//===-- LOVEMCTargetDesc.h - LOVE Target Descriptions -----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides LOVE specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_LOVE_MCTARGETDESC_LOVEMCTARGETDESC_H
#define LLVM_LIB_TARGET_LOVE_MCTARGETDESC_LOVEMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class Target;
class Triple;

extern Target TheLOVETarget;

} // End llvm namespace

// Defines symbolic names for LOVE registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "LOVEGenRegisterInfo.inc"

// Defines symbolic names for the LOVE instructions.
#define GET_INSTRINFO_ENUM
#include "LOVEGenInstrInfo.inc"

#endif
