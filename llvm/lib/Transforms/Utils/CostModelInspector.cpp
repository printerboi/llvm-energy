//===-- CostModelInspectorPass.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Utils/CostModelInspector.h"

using namespace llvm;

PreservedAnalyses CostModelInspectorPass::run(Function &F, FunctionAnalysisManager &AM) {
  TargetTransformInfo &TTI = AM.getResult<TargetIRAnalysis>(F);

  for(BasicBlock &BB : F) {
    for(Instruction &Inst : BB) {
        llvm::errs() << Inst.getOpcodeName() << " -> ";
        
        Value *Arg0 = Inst.getOperand(0);
        bool IsArg0Constant = isa<UndefValue>(Arg0) || isa<ConstantInt>(Arg0) ||
                                isa<ConstantFP>(Arg0);
        TargetTransformInfo::OperandValueInfo Arg0Info, Arg1Info;
        if (IsArg0Constant)
            Arg0Info.Kind = TargetTransformInfo::OK_UniformConstantValue;
        else
            Arg1Info.Kind = TargetTransformInfo::OK_UniformConstantValue;

        InstructionCost cost = TTI.getInstructionCost(&Inst, TTI::TargetCostKind::TCK_Energy);

        llvm::errs() << cost << "\n";
    }
  }
  return PreservedAnalyses::all();
}
