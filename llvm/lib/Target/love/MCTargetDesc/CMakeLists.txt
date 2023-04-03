add_llvm_component_library(LLVMloveDesc
  loveInstPrinter.cpp
  loveMCAsmInfo.cpp
  loveMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  loveInfo
  Support

  ADD_TO_COMPONENT
  love
  )
