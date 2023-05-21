#include "loveInfo.h"

#define GET_REGINFO_ENUM
#include "loveGenRegisterInfo.inc"

namespace llvm {
namespace loveABI {
MCRegister getBPReg() { return love::X9; }
MCRegister getSCSPReg() { return love::X18; }
} // namespace loveABI
} // namespace llvm
