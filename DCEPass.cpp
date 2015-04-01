#define DEBUG_TYPE "DCEPass"

#include "DCEPass.h"
#include <unordered_set>
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace cs380c;
using namespace llvm;

STATISTIC(NumInstRemoved, "The # of dead instructions removed by DCEPass");

bool DCEPass::runOnFunction(Function& f)
{

	std::unordered_set<StringRef, StringRefHash, StringRefEqual> initialSet;
	dfa->setInitialValues(initialSet);
	dfa->doDFA(f);
	return false;
}

void DCEPass::getAnalysisUsage(AnalysisUsage &AU) const
{
	AU.setPreservesCFG();
}

char DCEPass::ID = 0;
static RegisterPass<DCEPass> X("dce-pass", "Faintness Analysis and dead code elimination for LLVM top-level vars");



