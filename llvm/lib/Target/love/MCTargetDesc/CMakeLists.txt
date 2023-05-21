add_llvm_component_library(LLVMloveDesc
  loveInstPrinter.cpp
  loveMCAsmInfo.cpp
  loveMCTargetDesc.cpp
  loveInfo.cpp
  loveAsmBackend.cpp
  loveMCCodeEmitter.cpp
  loveMCExpr.cpp
  loveELFObjectWriter.cpp
  loveTargetStreamer.cpp
  loveELFStreamer.cpp
  loveMCObjectFIleInfo.cpp

  LINK_COMPONENTS
  MC
  loveInfo
  Support

  ADD_TO_COMPONENT
  love
  )
