#ifndef __LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCEXPR_H__
#define __LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCEXPR_H__

#include "llvm/MC/MCExpr.h"

namespace llvm {

class StringRef;

class loveMCExpr : public MCTargetExpr {
public:
  enum VariantKind {
    VK_love_None,
    VK_love_LO,
    VK_love_HI,
    VK_love_PCREL_LO,
    VK_love_PCREL_HI,
    VK_love_GOT_HI,
    VK_love_TPREL_LO,
    VK_love_TPREL_HI,
    VK_love_TPREL_ADD,
    VK_love_TLS_GOT_HI,
    VK_love_TLS_GD_HI,
    VK_love_CALL,
    VK_love_CALL_PLT,
    VK_love_32_PCREL,
    VK_love_Invalid // Must be the last item
  };

private:
  const MCExpr *Expr;
  const VariantKind Kind;

  int64_t evaluateAsInt64(int64_t Value) const;

  explicit loveMCExpr(const MCExpr *Expr, VariantKind Kind)
      : Expr(Expr), Kind(Kind) {}

public:
  static const loveMCExpr *create(const MCExpr *Expr, VariantKind Kind,
                                 MCContext &Ctx);

  VariantKind getKind() const { return Kind; }

  const MCExpr *getSubExpr() const { return Expr; }

  /// Get the corresponding PC-relative HI fixup that a VK_love_PCREL_LO
  /// points to, and optionally the fragment containing it.
  ///
  /// \returns nullptr if this isn't a VK_love_PCREL_LO pointing to a
  /// known PC-relative HI fixup.
  const MCFixup *getPCRelHiFixup(const MCFragment **DFOut) const;

  void printImpl(raw_ostream &OS, const MCAsmInfo *MAI) const override;
  bool evaluateAsRelocatableImpl(MCValue &Res, const MCAsmLayout *Layout,
                                 const MCFixup *Fixup) const override;
  void visitUsedExpr(MCStreamer &Streamer) const override;
  MCFragment *findAssociatedFragment() const override {
    return getSubExpr()->findAssociatedFragment();
  }

  void fixELFSymbolsInTLSFixups(MCAssembler &Asm) const override;

  bool evaluateAsConstant(int64_t &Res) const;

  static bool classof(const MCExpr *E) {
    return E->getKind() == MCExpr::Target;
  }

  static bool classof(const loveMCExpr *) { return true; }

  static VariantKind getVariantKindForName(StringRef name);
  static StringRef getVariantKindName(VariantKind Kind);
};

} // end namespace llvm.

#endif // __LLVM_LIB_TARGET_SIM_MCTARGETDESC_SIMMCEXPR_H__
