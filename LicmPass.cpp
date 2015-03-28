#define DEBUG_TYPE "LicmPass"

#include "LicmPass.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"

using namespace cs380c;
using namespace llvm;

STATISTIC(NumInstHoisted, "The # of instructions hoisted by LicmPass");

bool LicmPass::runOnLoop(llvm::Loop* loop, llvm::LPPassManager& lpm)
{
	// Remove the following two lines before you write down your own codes
	errs() << "Hello, " << *loop << "\n";
	return false;
}

void LicmPass::getAnalysisUsage(AnalysisUsage &AU) const
{
	AU.addRequired<LoopInfo>();
	AU.setPreservesCFG();
}

char LicmPass::ID = 0;
static RegisterPass<LicmPass> X("licm-pass", "Loop invariant code motion for LLVM top-level vars");
