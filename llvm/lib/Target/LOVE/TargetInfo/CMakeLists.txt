add_llvm_component_library(LLVMLOVEInfo
  LOVETargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  LOVE
  )
