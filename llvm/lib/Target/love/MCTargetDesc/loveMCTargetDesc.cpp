#include "loveMCTargetDesc.h"
#include "TargetInfo/loveTargetInfo.h"
#include "loveInfo.h"
#include "loveInstPrinter.h"
#include "loveELFStreamer.h"
#include "loveMCObjectFIleInfo.h"
#include "loveMCAsmInfo.h"
#include "loveTargetStreamer.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "loveGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "loveGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "loveGenSubtargetInfo.inc"

static MCInstrInfo *createloveMCInstrInfo() {
  auto *X = new MCInstrInfo();
  InitloveMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createloveMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitloveMCRegisterInfo(X, love::X1);
  return X;
}

static MCSubtargetInfo *createloveMCSubtargetInfo(const Triple &TT,
                                                  StringRef CPU, StringRef FS) {
  return createloveMCSubtargetInfoImpl(TT, CPU, /*TuneCPU=*/CPU, FS);
}

static MCAsmInfo *createloveMCAsmInfo(const MCRegisterInfo &MRI,
                                      const Triple &TT,
                                      const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new loveMCAsmInfo(TT);
  MCRegister SP = MRI.getDwarfRegNum(love::X2, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createloveMCInstPrinter(const Triple &T,
                                              unsigned SyntaxVariant,
                                              const MCAsmInfo &MAI,
                                              const MCInstrInfo &MII,
                                              const MCRegisterInfo &MRI) {
  return new loveInstPrinter(MAI, MII, MRI);
}

static MCTargetStreamer *createloveTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new loveTargetStreamer(S);
}

static MCObjectFileInfo *
createloveMCObjectFileInfo(MCContext &Ctx, bool PIC,
                            bool LargeCodeModel = false) {
  MCObjectFileInfo *MOFI = new loveMCObjectFileInfo();
  MOFI->initMCObjectFileInfo(Ctx, PIC, LargeCodeModel);
  return MOFI;
}

static MCTargetStreamer *
createloveObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
  const Triple &TT = STI.getTargetTriple();
  if (TT.isOSBinFormatELF())
    return new loveTargetELFStreamer(S, STI);
  return nullptr;
}

class loveMCInstrAnalysis : public MCInstrAnalysis {
public:
  explicit loveMCInstrAnalysis(const MCInstrInfo *Info)
      : MCInstrAnalysis(Info) {}

  bool evaluateBranch(const MCInst &Inst, uint64_t Addr, uint64_t Size,
                      uint64_t &Target) const override {
    if (isConditionalBranch(Inst)) {
      int64_t Imm;
      if (Size == 2)
        Imm = Inst.getOperand(1).getImm();
      else
        Imm = Inst.getOperand(2).getImm();
      Target = Addr + Imm;
      return true;
    }

    if (Inst.getOpcode() == love::JAL) {
      Target = Addr + Inst.getOperand(1).getImm();
      return true;
    }

    return false;
  }
};

static MCInstrAnalysis *createloveInstrAnalysis(const MCInstrInfo *Info) {
  return new loveMCInstrAnalysis(Info);
}

static MCTargetStreamer *createloveNullTargetStreamer(MCStreamer &S) {
  return new loveTargetStreamer(S);
}

namespace {
MCStreamer *createloveELFStreamer(const Triple &T, MCContext &Context,
                                   std::unique_ptr<MCAsmBackend> &&MAB,
                                   std::unique_ptr<MCObjectWriter> &&MOW,
                                   std::unique_ptr<MCCodeEmitter> &&MCE,
                                   bool RelaxAll) {
  return createloveELFStreamer(Context, std::move(MAB), std::move(MOW),
                                std::move(MCE), RelaxAll);
}
} // end anonymous namespace

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeloveTargetMC() {
  // Register the MC asm info.
  Target &TheloveTarget = getTheloveTarget();
  RegisterMCAsmInfoFn X(TheloveTarget, createloveMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCObjectFileInfo(TheloveTarget, createloveMCObjectFileInfo);
  TargetRegistry::RegisterMCInstrInfo(TheloveTarget, createloveMCInstrInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheloveTarget, createloveMCRegisterInfo);

  TargetRegistry::RegisterMCAsmBackend(TheloveTarget, createloveAsmBackend);
  TargetRegistry::RegisterMCCodeEmitter(TheloveTarget, createloveMCCodeEmitter);
  TargetRegistry::RegisterMCInstPrinter(TheloveTarget, createloveMCInstPrinter);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheloveTarget,
                                          createloveMCSubtargetInfo);
  TargetRegistry::RegisterELFStreamer(TheloveTarget, createloveELFStreamer);
  TargetRegistry::RegisterObjectTargetStreamer(
        TheloveTarget, createloveObjectTargetStreamer);
  TargetRegistry::RegisterMCInstrAnalysis(TheloveTarget, createloveInstrAnalysis);
  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheloveTarget, createloveMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheloveTarget,
                                            createloveTargetAsmStreamer);

  TargetRegistry::RegisterNullTargetStreamer(TheloveTarget,
                                               createloveNullTargetStreamer);                   
}
