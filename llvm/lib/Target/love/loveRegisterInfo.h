#ifndef __LLVM_LIB_TARGET_SIM_SIMREGISTERINFO_H__
#define __LLVM_LIB_TARGET_SIM_SIMREGISTERINFO_H__

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "loveGenRegisterInfo.inc"

namespace llvm {

class TargetInstrInfo;
class loveSubtarget;

struct loveRegisterInfo : public loveGenRegisterInfo {
public:
  loveRegisterInfo();

  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;

  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool requiresRegisterScavenging(const MachineFunction &MF) const override;

  void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  // Debug information queries.
  Register getFrameRegister(const MachineFunction &MF) const override;
};

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_SIM_SIMREGISTERINFO_H__
