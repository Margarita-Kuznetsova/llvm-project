//===-- loveTargetStreamer.cpp - love Target Streamer Methods -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides love specific target streamer methods.
//
//===----------------------------------------------------------------------===//

#include "loveTargetStreamer.h"
#include "loveInfo.h"
#include "loveMCTargetDesc.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/loveAttributes.h"
#include "llvm/Support/loveISAInfo.h"

using namespace llvm;

loveTargetStreamer::loveTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}

void loveTargetStreamer::finish() { finishAttributeSection(); }

void loveTargetStreamer::emitDirectiveOptionPush() {}
void loveTargetStreamer::emitDirectiveOptionPop() {}
void loveTargetStreamer::emitDirectiveOptionPIC() {}
void loveTargetStreamer::emitDirectiveOptionNoPIC() {}
void loveTargetStreamer::emitDirectiveOptionRVC() {}
void loveTargetStreamer::emitDirectiveOptionNoRVC() {}
void loveTargetStreamer::emitDirectiveOptionRelax() {}
void loveTargetStreamer::emitDirectiveOptionNoRelax() {}
void loveTargetStreamer::emitAttribute(unsigned Attribute, unsigned Value) {}
void loveTargetStreamer::finishAttributeSection() {}
void loveTargetStreamer::emitTextAttribute(unsigned Attribute,
                                            StringRef String) {}
void loveTargetStreamer::emitIntTextAttribute(unsigned Attribute,
                                               unsigned IntValue,
                                               StringRef StringValue) {}

void loveTargetStreamer::emitTargetAttributes(const MCSubtargetInfo &STI) {
//   if (STI.hasFeature(love::FeatureRV32E))
//     emitAttribute(loveAttrs::STACK_ALIGN, loveAttrs::ALIGN_4);
//   else
    emitAttribute(loveAttrs::STACK_ALIGN, loveAttrs::ALIGN_16);

  unsigned XLen = 32;
  std::vector<std::string> FeatureVector;
  loveFeatures::toFeatureVector(FeatureVector, STI.getFeatureBits());

  auto ParseResult = llvm::loveISAInfo::parseFeatures(XLen, FeatureVector);
  if (!ParseResult) {
    /* Assume any error about features should handled earlier.  */
    consumeError(ParseResult.takeError());
    llvm_unreachable("Parsing feature error when emitTargetAttributes?");
  } else {
    auto &ISAInfo = *ParseResult;
    emitTextAttribute(loveAttrs::ARCH, ISAInfo->toString());
  }
}

// This part is for ascii assembly output
loveTargetAsmStreamer::loveTargetAsmStreamer(MCStreamer &S,
                                               formatted_raw_ostream &OS)
    : loveTargetStreamer(S), OS(OS) {}

void loveTargetAsmStreamer::emitDirectiveOptionPush() {
  OS << "\t.option\tpush\n";
}

void loveTargetAsmStreamer::emitDirectiveOptionPop() {
  OS << "\t.option\tpop\n";
}

void loveTargetAsmStreamer::emitDirectiveOptionPIC() {
  OS << "\t.option\tpic\n";
}

void loveTargetAsmStreamer::emitDirectiveOptionNoPIC() {
  OS << "\t.option\tnopic\n";
}

void loveTargetAsmStreamer::emitDirectiveOptionRVC() {
  OS << "\t.option\trvc\n";
}

void loveTargetAsmStreamer::emitDirectiveOptionNoRVC() {
  OS << "\t.option\tnorvc\n";
}

void loveTargetAsmStreamer::emitDirectiveOptionRelax() {
  OS << "\t.option\trelax\n";
}

void loveTargetAsmStreamer::emitDirectiveOptionNoRelax() {
  OS << "\t.option\tnorelax\n";
}

void loveTargetAsmStreamer::emitAttribute(unsigned Attribute, unsigned Value) {
  OS << "\t.attribute\t" << Attribute << ", " << Twine(Value) << "\n";
}

void loveTargetAsmStreamer::emitTextAttribute(unsigned Attribute,
                                               StringRef String) {
  OS << "\t.attribute\t" << Attribute << ", \"" << String << "\"\n";
}

void loveTargetAsmStreamer::emitIntTextAttribute(unsigned Attribute,
                                                  unsigned IntValue,
                                                  StringRef StringValue) {}

void loveTargetAsmStreamer::finishAttributeSection() {}
