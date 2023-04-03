#ifndef LLVM_LIB_TARGET_love_MCTARGETDESC_loveINFO_H
#define LLVM_LIB_TARGET_love_MCTARGETDESC_loveINFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace loveCC {
enum CondCode {
  EQ,
  NE,
  LE,
  GT,
  LEU,
  GTU,
  INVALID,
};

CondCode getOppositeBranchCondition(CondCode);

enum BRCondCode {
  BREQ = 0x0,
};
} // end namespace loveCC

namespace loveOp {
enum OperandType : unsigned {
  OPERAND_LOVEM16 = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_UIMM16,
};
} // namespace loveOp

} // end namespace llvm

#endif
