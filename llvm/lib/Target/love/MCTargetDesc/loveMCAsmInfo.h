#ifndef LLVM_LIB_TARGET_love_MCTARGETDESC_loveMCASMINFO_H
#define LLVM_LIB_TARGET_love_MCTARGETDESC_loveMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class loveMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit loveMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_love_MCTARGETDESC_loveMCASMINFO_H
