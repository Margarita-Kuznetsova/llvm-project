//===-- LOVE.td - Describe the LOVE Target Machine ----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This is the top level entry point for the LOVE target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

include "LOVERegisterInfo.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "LOVEInstrInfo.td"
def LOVEInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// LOVE processors supported.
//===----------------------------------------------------------------------===//

// Will generate LOVEGenAsmWrite.inc included by LOVEInstPrinter.cpp, contents
//  as follows,
// void LOVEInstPrinter::printInstruction(const MCInst *MI, raw_ostream &O) {...}
// const char *LOVEInstPrinter::getRegisterName(unsigned RegNo) {...}
def LOVE : Target {
  let InstructionSet = LOVEInstrInfo;
}
