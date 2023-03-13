add_llvm_component_library(LLVMLOVEDesc
  LOVEMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  LOVEInfo
  Support

  ADD_TO_COMPONENT
  LOVE
  )
