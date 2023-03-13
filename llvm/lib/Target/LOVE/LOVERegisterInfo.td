//===-- LOVERegisterInfo.td - LOVE Register defs -----------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the LOVE register file
//===----------------------------------------------------------------------===//

// For tablegen(... -gen-emitter)  in CMakeLists.txt
class LOVEReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
}

// LOVE CPU Registers
class LOVEGPRReg<bits<16> Enc, string n> : LOVEReg<Enc, n>;

//===----------------------------------------------------------------------===//
//@Registers
//===----------------------------------------------------------------------===//
//@ All registers definition
let Namespace = "LOVE" in {
  //@ General Purpose Registers
  def R0    : LOVEGPRReg<0,  "r0">,    DwarfRegNum<[0]>;
  def R1    : LOVEGPRReg<1,  "r1">,    DwarfRegNum<[1]>;
  def R2    : LOVEGPRReg<2,  "r2">,    DwarfRegNum<[2]>;
  def R3    : LOVEGPRReg<3,  "r3">,    DwarfRegNum<[3]>;
  def R4    : LOVEGPRReg<4,  "r4">,    DwarfRegNum<[4]>;
  def R5    : LOVEGPRReg<5,  "r5">,    DwarfRegNum<[5]>;
  def R6    : LOVEGPRReg<6,  "r6">,    DwarfRegNum<[6]>;
  def R7    : LOVEGPRReg<7,  "r7">,    DwarfRegNum<[7]>;
  def R8    : LOVEGPRReg<8,  "r8">,    DwarfRegNum<[8]>;
  def R9    : LOVEGPRReg<9,  "r9">,    DwarfRegNum<[9]>;
  def R10   : LOVEGPRReg<10, "r10">,   DwarfRegNum<[10]>;
  def R11   : LOVEGPRReg<11, "r11">,   DwarfRegNum<[11]>;
  def R12   : LOVEGPRReg<12, "r12">,   DwarfRegNum<[12]>;
  def R13   : LOVEGPRReg<13, "r13">,   DwarfRegNum<[13]>;
  def R14   : LOVEGPRReg<14, "r14">,   DwarfRegNum<[14]>;
  def R15   : LOVEGPRReg<15, "r15">,   DwarfRegNum<[15]>;
}

//===----------------------------------------------------------------------===//
//@Register Classes
//===----------------------------------------------------------------------===//

def CPURegs : RegisterClass<"LOVE", [i32], 32, (add
  R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15)>;
