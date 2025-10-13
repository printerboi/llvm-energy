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
    return std::make_unique<InlineAdvice>(this, CB, getCallerORE(CB), false);
  }

  if (!Callee || Callee->isDeclaration() || Callee->isIntrinsic()) {
    return std::make_unique<InlineAdvice>(this, CB, getCallerORE(CB), false);
  }

  if (CB.getCaller() == Callee){
    return std::make_unique<InlineAdvice>(this, CB, getCallerORE(CB), false);
  }
  

  // Query per-function TTI if you want to use it in cost model.
  TargetTransformInfo &CallerTTI = FAM.getResult<TargetIRAnalysis>(*Caller);
  TargetTransformInfo &CalleeTTI = FAM.getResult<TargetIRAnalysis>(*Callee);
  (void)CallerTTI;
  (void)CalleeTTI;

  if(callcost <= 0){
    SmallVector<Value *, 4> DummyArgs;
    for (Type *ParamTy : Callee->getFunctionType()->params()) {
      // Use UndefValue for simplicity
      DummyArgs.push_back(UndefValue::get(ParamTy));
    }

    // Create a temporary call instruction (not inserted into any block)
    CallInst *TmpCall = CallInst::Create(Callee, DummyArgs);

    callcost = CalleeTTI.getInstructionCost(TmpCall, TTI::TCK_Energy);
    delete TmpCall;
  }

  // Query function costs
  InstructionCost CallerEnergy = 0.0;
  InstructionCost CalleeEnergy = 0.0;

  StringRef CallerName = Caller->getName();
  StringRef CalleeName = Callee->getName();

  // Check if caller is cached
  if(this->callercache.find(CallerName) == this->callercache.end()){
    CallerEnergy = computeFunctionEnergy(Caller, &CalleeTTI);
    this->callercache[CallerName] = CallerEnergy;
  }else{
    CallerEnergy = this->callercache[CallerName];
  }

  // Check if callee is cached
  if(this->calleecache.find(CalleeName) == this->calleecache.end()){
    CalleeEnergy = computeFunctionEnergy(Callee, &CalleeTTI);
    this->calleecache[CalleeName] = CalleeEnergy;
  }else{
    CalleeEnergy = this->calleecache[CalleeName];
  }
  
  InstructionCost engWhenInlined = estimateInlinedEnergy(CallerEnergy, CalleeEnergy);
  InstructionCost sum = CallerEnergy + CalleeEnergy;
  InstructionCost EnergyGain = sum - engWhenInlined;

  bool si = EnergyGain > 7.6e-02;
  //bool si = EnergyGain > 0.0;

    /* dbgs() << "Energy inline decision for call '"
                  << CB.getCalledFunction()->getName() << "':\n"
                  << "  CallerEnergy = " << CallerEnergy << "\n"
                  << "  CalleeEnergy = " << CalleeEnergy << "\n"
                  << "  Sum = " << sum  << "\n"
                  << "  Inline = " << engWhenInlined << "\n"
                  << "  Diff = " << sum - engWhenInlined << "\n"
                  << "  EstimatedGain = " << EnergyGain.getValue() << "\n"
                  << "  ShouldInline = " << si << "\n"; */

  InlineCost IC = si
                        ? InlineCost::getAlways("energy heuristic: profitable")
                        : InlineCost::getNever("energy heuristic: unprofitable");


  // Create DefaultInlineAdvice with no InlineCost (std::nullopt) and the ORE from the advisor.
  //return std::make_unique<DefaultInlineAdvice>(this, CB, IC, getCallerORE(CB), false);
  return std::make_unique<InlineAdvice>(this, CB, getCallerORE(CB), si);
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

InstructionCost EnergyAwareInlineAdvisor::estimateInlinedEnergy(InstructionCost callercost, InstructionCost calleecost) {
  // Simple heuristic: assume inlining saves some fraction of callee's energy.
  return callercost + 0.8 * calleecost - callcost;
}
