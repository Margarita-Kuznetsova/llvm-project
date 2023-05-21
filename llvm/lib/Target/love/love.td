//===----------------------------------------------------------------------===//
// This is the top level entry point for the love target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// love Subtarget features
//===----------------------------------------------------------------------===//

//def FeatureDummy
//    : SubtargetFeature<"dummy", "Dummy", "true",
//                       "Dummy feature">;

defvar love32 = DefaultMode;

//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

include "loveRegisterInfo.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "loveSchedule.td"
include "loveCallingConv.td"

include "loveInstrInfo.td"
def loveInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// love processors supported.
//===----------------------------------------------------------------------===//

def : ProcessorModel<"generic-32", NoSchedModel, []>;

def loveAsmParser : AsmParser {
  let ShouldEmitMatchRegisterAltName = 1;
  let AllowDuplicateRegisterNames = 1;
}


// Will generate loveGenAsmWrite.inc included by loveInstPrinter.cpp, contents
//  as follows,
// void loveInstPrinter::printInstruction(const MCInst *MI, raw_ostream &O) {...}
// const char *loveInstPrinter::getRegisterName(unsigned RegNo) {...}
def love : Target {
  let InstructionSet = loveInstrInfo;
}
