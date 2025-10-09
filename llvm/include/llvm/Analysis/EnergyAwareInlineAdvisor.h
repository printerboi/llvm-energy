#ifndef LLVM_ANALYSIS_ENERGYAWAREINLINEADVISOR_H
#define LLVM_ANALYSIS_ENERGYAWAREINLINEADVISOR_H

#include "llvm/Analysis/InlineAdvisor.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include <memory>

namespace llvm {

/// EnergyAwareInlineAdvisor
/// Decides whether to inline based on an energy model. Uses FunctionAnalysisManager
/// to query per-function TargetTransformInfo and the InlineAdvisor infrastructure
/// for remark emission.
class EnergyAwareInlineAdvisor : public DefaultInlineAdvisor {
public:
  /// Construct the advisor with module context and FunctionAnalysisManager.
  EnergyAwareInlineAdvisor(Module &M, FunctionAnalysisManager &FAM,
                           InlineParams Params, InlineContext IC);

private:
  /// Reference to the FunctionAnalysisManager for per-function analyses.
  FunctionAnalysisManager &FAM;

  /// Main hook invoked by the inliner for every callsite.
  std::unique_ptr<InlineAdvice> getAdviceImpl(CallBase &CB) override;

  /// Compute total energy cost of a function (placeholder model).
  InstructionCost computeFunctionEnergy(Function *F, TargetTransformInfo *TTI);

  /// Estimate the energy after inlining (placeholder heuristic).
  InstructionCost estimateInlinedEnergy(Function *Caller, TargetTransformInfo *CallerTTI, Function *Callee, TargetTransformInfo *CalleeTTI);

  InstructionCost callcost = -1.0;
};

} // namespace llvm

#endif // LLVM_ANALYSIS_ENERGYAWAREINLINEADVISOR_H
