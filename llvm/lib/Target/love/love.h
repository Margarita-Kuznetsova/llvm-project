#ifndef __LLVM_LIB_TARGET_SIM_SIM_H__
#define __LLVM_LIB_TARGET_SIM_SIM_H__

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


// namespace love {
// enum {
// };
// } // namespace love

} // namespace llvm

#endif // __LLVM_LIB_TARGET_SIM_SIM_H__
