#ifndef LLVM_LIB_TARGET_love_MCTARGETDESC_loveMCTARGETDESC_H
#define LLVM_LIB_TARGET_love_MCTARGETDESC_loveMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

#include <memory>

namespace llvm {
class Target;
class Triple;

extern Target TheloveTarget;

} // End llvm namespace

// Defines symbolic names for love registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "loveGenRegisterInfo.inc"

// Defines symbolic names for the love instructions.
#define GET_INSTRINFO_ENUM
#include "loveGenInstrInfo.inc"

#endif
