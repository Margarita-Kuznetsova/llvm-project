add_llvm_component_group(LOVE)

set(LLVM_TARGET_DEFINITIONS LOVE.td)

# Generate LOVEGenRegisterInfo.inc and LOVEGenInstrInfo.inc which included by
#  your hand code C++ files.
# LOVEGenRegisterInfo.inc came from LOVERegisterInfo.td, LOVEGenInstrInfo.inc
#  came from LOVEInstrInfo.td.
tablegen(LLVM LOVEGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM LOVEGenInstrInfo.inc -gen-instr-info)

# LOVECommonTableGen must be defined
add_public_tablegen_target(LOVECommonTableGen)

# LOVECodeGen should match with LLVMBuild.txt LOVECodeGen
add_llvm_target(LOVECodeGen
  LOVETargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  LOVEDesc
  LOVEInfo
  SelectionDAG
  Support
  Target
  GlobalISel

  ADD_TO_COMPONENT
  LOVE
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
