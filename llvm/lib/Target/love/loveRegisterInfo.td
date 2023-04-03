//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the love register file
//===----------------------------------------------------------------------===//

// For tablegen(... -gen-emitter)  in CMakeLists.txt
class loveReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
}

//===----------------------------------------------------------------------===//
//@Registers
//===----------------------------------------------------------------------===//
//@ All registers definition
let Namespace = "love" in {
  //@ General Purpose Registers
  def R0    : loveReg<0,  "r0">,    DwarfRegNum<[0]>;  // gp?
  def R1    : loveReg<1,  "r1">,    DwarfRegNum<[1]>;  // ra
  def R2    : loveReg<2,  "r2">,    DwarfRegNum<[2]>;  // sp
  def R3    : loveReg<3,  "r3">,    DwarfRegNum<[3]>;  // fp
  def R4    : loveReg<4,  "r4">,    DwarfRegNum<[4]>;  // bp
  def R5    : loveReg<5,  "r5">,    DwarfRegNum<[5]>;  // s0
  def R6    : loveReg<6,  "r6">,    DwarfRegNum<[6]>;  // s1
  def R7    : loveReg<7,  "r7">,    DwarfRegNum<[7]>;  // s2
  def R8    : loveReg<8,  "r8">,    DwarfRegNum<[8]>;  // s3
  def R9    : loveReg<9,  "r9">,    DwarfRegNum<[9]>;  // a0
  def R10   : loveReg<10, "r10">,   DwarfRegNum<[10]>; // a1
  def R11   : loveReg<11, "r11">,   DwarfRegNum<[11]>; // a2
  def R12   : loveReg<12, "r12">,   DwarfRegNum<[12]>; // a3
  def R13   : loveReg<13, "r13">,   DwarfRegNum<[13]>; // t0
  def R14   : loveReg<14, "r14">,   DwarfRegNum<[14]>; // t1
  def R15   : loveReg<15, "r15">,   DwarfRegNum<[15]>; // t2
}

//===----------------------------------------------------------------------===//
//@Register Classes
//===----------------------------------------------------------------------===//

def GPR : RegisterClass<"love", [i32], 32, (add
  R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15)>;
