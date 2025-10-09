#include "llvm/Analysis/EnergyAwareInlineAdvisor.h"

#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/Support/Debug.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/Constants.h"

#include <optional>

using namespace llvm;

#define DEBUG_TYPE "energy-inline-advisor"

#define CONTEXT_SWITCH_COST 0.05

EnergyAwareInlineAdvisor::EnergyAwareInlineAdvisor(Module &M,
                                                   FunctionAnalysisManager &FAM,
                                                   InlineParams Params,
                                                   InlineContext IC)
    : DefaultInlineAdvisor(M, FAM, Params, IC), FAM(FAM) {}

std::unique_ptr<InlineAdvice> EnergyAwareInlineAdvisor::getAdviceImpl(CallBase &CB) {
  //llvm::outs() << "I WAS CALLED" << "\n";

  Function *Caller = CB.getFunction();
  Function *Callee = CB.getCalledFunction();

  // If there is no direct callee (indirect call), do not inline.
  if (!Callee) {
    // Build DefaultInlineAdvice: Advisor* = this, optional InlineCost = none,
    // ORE = getCallerORE(CB), EmitRemarks = false (or true if you want remarks).
    return std::make_unique<DefaultInlineAdvice>(this, CB, std::optional<InlineCost>{},
                                                 getCallerORE(CB), /*EmitRemarks=*/false);
  }

  // Query per-function TTI if you want to use it in cost model.
  TargetTransformInfo &CallerTTI = FAM.getResult<TargetIRAnalysis>(*Caller);
  TargetTransformInfo &CalleeTTI = FAM.getResult<TargetIRAnalysis>(*Callee);
  (void)CallerTTI;
  (void)CalleeTTI;

  InstructionCost CallerEnergy = computeFunctionEnergy(Caller, &CalleeTTI);
  InstructionCost CalleeEnergy = computeFunctionEnergy(Callee, &CalleeTTI);
  InstructionCost engWhenInlined = estimateInlinedEnergy(Caller, &CallerTTI, Callee, &CalleeTTI);
  InstructionCost sum = CallerEnergy + CalleeEnergy;

  InstructionCost EnergyGain = sum - engWhenInlined;

  bool ShouldInline = EnergyGain > 2.0e-2;

/*   dbgs() << "Energy inline decision for call '"
                    << CB.getCalledFunction()->getName() << "':\n"
                    << "  CallerEnergy = " << CallerEnergy << "\n"
                    << "  CalleeEnergy = " << CalleeEnergy << "\n"
                    << "  Sum = " << sum  << "\n"
                    << "  Inline = " << engWhenInlined << "\n"
                    << "  Diff = " << sum - engWhenInlined << "\n"
                    << "  EstimatedGain = " << EnergyGain.getValue() << "\n"
                    << "  ShouldInline = " << ShouldInline << "\n"; */


    InlineCost IC = ShouldInline
                        ? InlineCost::getAlways("energy heuristic: profitable")
                        : InlineCost::getNever("energy heuristic: unprofitable");

  // Create DefaultInlineAdvice with no InlineCost (std::nullopt) and the ORE from the advisor.
  return std::make_unique<DefaultInlineAdvice>(this, CB, IC,
                                               getCallerORE(CB), /*EmitRemarks=*/true);
}

InstructionCost EnergyAwareInlineAdvisor::computeFunctionEnergy(Function *F, TargetTransformInfo *TTI) {
  // Placeholder energy model: replace with real per-instruction energy data.
  InstructionCost Total = 0.0;
  for (auto &BB : *F) {
    for (auto &I : BB) {
      InstructionCost cost = TTI->getInstructionCost(&I, TTI::TCK_Energy);
/*       if(I.getOpcode() == 56 || true){
        dbgs() << I.getOpcode() << "(" << I.getOpcodeName() << ")" << ": " << cost << "\n";
      } */
      Total += cost;
    }
  }

  //dbgs() << "Total: " << Total << "\n";

  return Total;
}

InstructionCost EnergyAwareInlineAdvisor::estimateInlinedEnergy(Function *Caller, TargetTransformInfo *CallerTTI, Function *Callee, TargetTransformInfo *CalleeTTI) {
  // Simple heuristic: assume inlining saves some fraction of callee's energy.

  SmallVector<Value *, 4> DummyArgs;
  for (Type *ParamTy : Callee->getFunctionType()->params()) {
    // Use UndefValue for simplicity
    DummyArgs.push_back(UndefValue::get(ParamTy));
  }

  if(callcost <= 0){
    // Create a temporary call instruction (not inserted into any block)
    CallInst *TmpCall = CallInst::Create(Callee, DummyArgs);

    callcost = CalleeTTI->getInstructionCost(TmpCall, TTI::TCK_Energy);
    delete TmpCall;
  }
  
  return computeFunctionEnergy(Caller, CallerTTI) + 0.8 * computeFunctionEnergy(Callee, CalleeTTI) - callcost;
}
