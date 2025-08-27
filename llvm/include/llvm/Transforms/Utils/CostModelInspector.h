//===-- CostModelInspector.h - Example Transformations ------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_UTILS_COSTMODELINSPECTOR_H
#define LLVM_TRANSFORMS_UTILS_COSTMODELINSPECTOR_H

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"


namespace llvm {

class CostModelInspectorPass : public PassInfoMixin<CostModelInspectorPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_COSTMODELINSPECTOR_H
