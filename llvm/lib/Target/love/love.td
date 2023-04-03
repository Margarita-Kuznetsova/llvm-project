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

//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

include "loveRegisterInfo.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "loveCallingConv.td"

include "loveInstrInfo.td"
def loveInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// love processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;
//def : Proc<"dummy-st", []>;

// Will generate loveGenAsmWrite.inc included by loveInstPrinter.cpp, contents
//  as follows,
// void loveInstPrinter::printInstruction(const MCInst *MI, raw_ostream &O) {...}
// const char *loveInstPrinter::getRegisterName(unsigned RegNo) {...}
def love : Target {
  let InstructionSet = loveInstrInfo;
}
