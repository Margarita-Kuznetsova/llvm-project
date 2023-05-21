//===----------------------------------------------------------------------===//
//
// This file declares love-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef __LLVM_LIB_TARGET_SIM_SIMMACHINEFUNCTIONINFO_H__
#define __LLVM_LIB_TARGET_SIM_SIMMACHINEFUNCTIONINFO_H__

#include "llvm/CodeGen/MachineFunction.h"
#include <vector>

namespace llvm {

/// loveFunctionInfo - This class is derived from MachineFunction private
/// love target-specific information for each MachineFunction.
class loveFunctionInfo : public MachineFunctionInfo {
  virtual void anchor();

  bool ReturnStackOffsetSet = false;
  unsigned ReturnStackOffset = -1U;

  /// FrameIndex for start of varargs area
  int VarArgsFrameIndex = 0;
  /// Size of the save area used for varargs
  int VarArgsSaveSize = 0;
  /// Size of stack frame to save callee saved registers
  unsigned CalleeSavedStackSize = 0;

public:
  loveFunctionInfo() {}
  explicit loveFunctionInfo(MachineFunction &MF) {}
  ~loveFunctionInfo() {}

  void setVarArgsFrameIndex(int Off) { VarArgsFrameIndex = Off; }
  int getVarArgsFrameIndex() const { return VarArgsFrameIndex; }

  void setVarArgsSaveSize(int Size) { VarArgsSaveSize = Size; }
  int getVarArgsSaveSize() const { return VarArgsSaveSize; }

  unsigned getCalleeSavedStackSize() const { return CalleeSavedStackSize; }
  void setCalleeSavedStackSize(unsigned Size) { CalleeSavedStackSize = Size; }

  void setReturnStackOffset(unsigned Off) {
    assert(!ReturnStackOffsetSet && "Return stack offset set twice");
    ReturnStackOffset = Off;
    ReturnStackOffsetSet = true;
  }

  unsigned getReturnStackOffset() const {
    assert(ReturnStackOffsetSet && "Return stack offset not set");
    return ReturnStackOffset;
  }

  // unsigned MaxCallStackReq = 0;
};

} // end namespace llvm

#endif // __LLVM_LIB_TARGET_SIM_SIMMACHINEFUNCTIONINFO_H__
