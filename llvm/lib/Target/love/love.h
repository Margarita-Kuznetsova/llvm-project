#ifndef LLVM_LIB_TARGET_love_love_H
#define LLVM_LIB_TARGET_love_love_H

#include "MCTargetDesc/loveMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class loveTargetMachine;
class FunctionPass;
class loveSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

bool lowerloveMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                    AsmPrinter &AP);
bool LowerloveMachineOperandToMCOperand(const MachineOperand &MO,
                                         MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createloveISelDag(loveTargetMachine &TM,
                                CodeGenOpt::Level OptLevel);


namespace love {
enum {
  GP = love::R0,
  RA = love::R1,
  SP = love::R2,
  FP = love::R3,
  BP = love::R4,
};
} // namespace love

} // namespace llvm

#endif
