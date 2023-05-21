//===-- loveELFObjectWriter.cpp - love ELF Writer -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/loveFixupKinds.h"
#include "MCTargetDesc/loveMCExpr.h"
#include "MCTargetDesc/loveMCTargetDesc.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class loveELFObjectWriter : public MCELFObjectTargetWriter {
public:
  loveELFObjectWriter(uint8_t OSABI, bool Is64Bit);

  ~loveELFObjectWriter() override;

  // Return true if the given relocation must be with a symbol rather than
  // section plus offset.
  bool needsRelocateWithSymbol(const MCSymbol &Sym,
                               unsigned Type) const override {
    // TODO: this is very conservative, update once RISC-V psABI requirements
    //       are clarified.
    return true;
  }

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};
}

loveELFObjectWriter::loveELFObjectWriter(uint8_t OSABI, bool Is64Bit)
    : MCELFObjectTargetWriter(Is64Bit, OSABI, ELF::EM_love,
                              /*HasRelocationAddend*/ true) {}

loveELFObjectWriter::~loveELFObjectWriter() {}

unsigned loveELFObjectWriter::getRelocType(MCContext &Ctx,
                                            const MCValue &Target,
                                            const MCFixup &Fixup,
                                            bool IsPCRel) const {
  const MCExpr *Expr = Fixup.getValue();
  // Determine the type of the relocation
  unsigned Kind = Fixup.getTargetKind();
  if (Kind >= FirstLiteralRelocationKind)
    return Kind - FirstLiteralRelocationKind;
  if (IsPCRel) {
    switch (Kind) {
    default:
      Ctx.reportError(Fixup.getLoc(), "Unsupported relocation type");
      return ELF::R_love_NONE;
    case FK_Data_4:
    case FK_PCRel_4:
      return ELF::R_love_32_PCREL;
    case love::fixup_love_pcrel_hi20:
      return ELF::R_love_PCREL_HI20;
    case love::fixup_love_pcrel_lo12_i:
      return ELF::R_love_PCREL_LO12_I;
    case love::fixup_love_pcrel_lo12_s:
      return ELF::R_love_PCREL_LO12_S;
    case love::fixup_love_got_hi20:
      return ELF::R_love_GOT_HI20;
    case love::fixup_love_tls_got_hi20:
      return ELF::R_love_TLS_GOT_HI20;
    case love::fixup_love_tls_gd_hi20:
      return ELF::R_love_TLS_GD_HI20;
    case love::fixup_love_jal:
      return ELF::R_love_JAL;
    case love::fixup_love_branch:
      return ELF::R_love_BRANCH;
    case love::fixup_love_rvc_jump:
      return ELF::R_love_RVC_JUMP;
    case love::fixup_love_rvc_branch:
      return ELF::R_love_RVC_BRANCH;
    case love::fixup_love_call:
      return ELF::R_love_CALL;
    case love::fixup_love_call_plt:
      return ELF::R_love_CALL_PLT;
    case love::fixup_love_add_8:
      return ELF::R_love_ADD8;
    case love::fixup_love_sub_8:
      return ELF::R_love_SUB8;
    case love::fixup_love_add_16:
      return ELF::R_love_ADD16;
    case love::fixup_love_sub_16:
      return ELF::R_love_SUB16;
    case love::fixup_love_add_32:
      return ELF::R_love_ADD32;
    case love::fixup_love_sub_32:
      return ELF::R_love_SUB32;
    case love::fixup_love_add_64:
      return ELF::R_love_ADD64;
    case love::fixup_love_sub_64:
      return ELF::R_love_SUB64;
    }
  }

  switch (Kind) {
  default:
    Ctx.reportError(Fixup.getLoc(), "Unsupported relocation type");
    return ELF::R_love_NONE;
  case FK_Data_1:
    Ctx.reportError(Fixup.getLoc(), "1-byte data relocations not supported");
    return ELF::R_love_NONE;
  case FK_Data_2:
    Ctx.reportError(Fixup.getLoc(), "2-byte data relocations not supported");
    return ELF::R_love_NONE;
  case FK_Data_4:
    if (Expr->getKind() == MCExpr::Target &&
        cast<loveMCExpr>(Expr)->getKind() == loveMCExpr::VK_love_32_PCREL)
      return ELF::R_love_32_PCREL;
    return ELF::R_love_32;
  case FK_Data_8:
    return ELF::R_love_64;
  case love::fixup_love_hi20:
    return ELF::R_love_HI20;
  case love::fixup_love_lo12_i:
    return ELF::R_love_LO12_I;
  case love::fixup_love_lo12_s:
    return ELF::R_love_LO12_S;
  case love::fixup_love_tprel_hi20:
    return ELF::R_love_TPREL_HI20;
  case love::fixup_love_tprel_lo12_i:
    return ELF::R_love_TPREL_LO12_I;
  case love::fixup_love_tprel_lo12_s:
    return ELF::R_love_TPREL_LO12_S;
  case love::fixup_love_tprel_add:
    return ELF::R_love_TPREL_ADD;
  case love::fixup_love_relax:
    return ELF::R_love_RELAX;
  case love::fixup_love_align:
    return ELF::R_love_ALIGN;
  case love::fixup_love_set_6b:
    return ELF::R_love_SET6;
  case love::fixup_love_sub_6b:
    return ELF::R_love_SUB6;
  case love::fixup_love_add_8:
    return ELF::R_love_ADD8;
  case love::fixup_love_set_8:
    return ELF::R_love_SET8;
  case love::fixup_love_sub_8:
    return ELF::R_love_SUB8;
  case love::fixup_love_set_16:
    return ELF::R_love_SET16;
  case love::fixup_love_add_16:
    return ELF::R_love_ADD16;
  case love::fixup_love_sub_16:
    return ELF::R_love_SUB16;
  case love::fixup_love_set_32:
    return ELF::R_love_SET32;
  case love::fixup_love_add_32:
    return ELF::R_love_ADD32;
  case love::fixup_love_sub_32:
    return ELF::R_love_SUB32;
  case love::fixup_love_add_64:
    return ELF::R_love_ADD64;
  case love::fixup_love_sub_64:
    return ELF::R_love_SUB64;
  }
}

std::unique_ptr<MCObjectTargetWriter>
llvm::createloveELFObjectWriter(uint8_t OSABI, bool Is64Bit) {
  return std::make_unique<loveELFObjectWriter>(OSABI, Is64Bit);
}
