add_llvm_component_library(LLVMloveInfo
  loveTargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  love
  )
