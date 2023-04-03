#include "loveMCTargetDesc.h"
#include "TargetInfo/loveTargetInfo.h"
#include "loveInfo.h"
#include "loveInstPrinter.h"
#include "loveMCAsmInfo.h"
#include "loveTargetStreamer.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "loveGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "loveGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "loveGenRegisterInfo.inc"

static MCInstrInfo *createloveMCInstrInfo() {
  auto *X = new MCInstrInfo();
  InitloveMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createloveMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitloveMCRegisterInfo(X, love::R1);
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
  MCRegister SP = MRI.getDwarfRegNum(love::R2, true);
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

loveTargetStreamer::loveTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
loveTargetStreamer::~loveTargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new loveTargetStreamer(S);
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeloveTargetMC() {
  // Register the MC asm info.
  Target &TheloveTarget = getTheloveTarget();
  RegisterMCAsmInfoFn X(TheloveTarget, createloveMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheloveTarget, createloveMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheloveTarget, createloveMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheloveTarget,
                                          createloveMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheloveTarget, createloveMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheloveTarget,
                                            createTargetAsmStreamer);
}
