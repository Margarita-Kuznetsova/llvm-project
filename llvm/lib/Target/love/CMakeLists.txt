add_llvm_component_group(love)

set(LLVM_TARGET_DEFINITIONS love.td)

# Generate loveGenRegisterInfo.inc and loveGenInstrInfo.inc which included by
#  your hand code C++ files.
# loveGenRegisterInfo.inc came from loveRegisterInfo.td, loveGenInstrInfo.inc
#  came from loveInstrInfo.td.
tablegen(LLVM loveGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM loveGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM loveGenCallingConv.inc -gen-callingconv)
tablegen(LLVM loveGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM loveGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM loveGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM loveGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM loveGenDAGISel.inc -gen-dag-isel)

#tablegen(LLVM loveGenDisassemblerTables.inc -gen-disassembler)

# loveCommonTableGen must be defined
add_public_tablegen_target(loveCommonTableGen)

# loveCodeGen should match with LLVMBuild.txt loveCodeGen
add_llvm_target(loveCodeGen
  loveAsmPrinter.cpp
  loveFrameLowering.cpp
  loveInstrInfo.cpp
  loveISelDagToDag.cpp
  loveISelLowering.cpp
  loveMachineFunctionInfo.cpp
  loveMCInstLower.cpp
  loveRegisterInfo.cpp
  loveSubtarget.cpp
  loveTargetMachine.cpp
  loveMatInt.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  loveDesc
  loveInfo
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  love
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
