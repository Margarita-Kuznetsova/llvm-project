//===----------------------------------------------------------------------===//
//
// Implements the info about love target spec.
//
//===----------------------------------------------------------------------===//

#include "loveTargetMachine.h"
#include "love.h"
//#include "loveTargetTransformInfo.h"
#include "TargetInfo/loveTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetOptions.h"

#define DEBUG_TYPE "love"

using namespace llvm;

static Reloc::Model getRelocModel(Optional<Reloc::Model> RM) {
  return RM.getValueOr(Reloc::Static);
}

/// loveTargetMachine ctor - Create an ILP32 Architecture model
loveTargetMachine::loveTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Optional<Reloc::Model> RM,
                                     Optional<CodeModel::Model> CM,
                                     CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T,
                        "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i32:32:32-"
                        "f32:32:32-i64:32-f64:32-a:0:32-n32",
                        TT, CPU, FS, Options, getRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

loveTargetMachine::~loveTargetMachine() = default;

namespace {

/// love Code Generator Pass Configuration Options.
class lovePassConfig : public TargetPassConfig {
public:
  lovePassConfig(loveTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  loveTargetMachine &getloveTargetMachine() const {
    return getTM<loveTargetMachine>();
  }

  bool addInstSelector() override;
  // void addPreEmitPass() override;
  // void addPreRegAlloc() override;
};

} // end anonymous namespace

TargetPassConfig *loveTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new lovePassConfig(*this, PM);
}

bool lovePassConfig::addInstSelector() {
  addPass(createloveISelDag(getloveTargetMachine(), getOptLevel()));
  return false;
}

// void lovePassConfig::addPreEmitPass() { llvm_unreachable(""); }

// void lovePassConfig::addPreRegAlloc() { llvm_unreachable(""); }

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeloveTarget() {
  RegisterTargetMachine<loveTargetMachine> X(getTheloveTarget());
}

#if 0
TargetTransformInfo
loveTargetMachine::getTargetTransformInfo(const Function &F) {
  return TargetTransformInfo(loveTTIImpl(this, F));
}
#endif