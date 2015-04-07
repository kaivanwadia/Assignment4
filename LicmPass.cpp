#define DEBUG_TYPE "LicmPass"

#include "LicmPass.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include <unordered_set>
#include "Equal.h"

using namespace cs380c;
using namespace llvm;

STATISTIC(NumInstHoisted, "The # of instructions hoisted by LicmPass");

bool LicmPass::runOnLoop(llvm::Loop* loop, llvm::LPPassManager& lpm)
{
	InstSet initialSet;
	dfa->setInitialValues(initialSet);
	LoopInfo& loopInfo = getAnalysis<LoopInfo>();
	dfa->doDFA(loop, lpm, loopInfo);

	// Delete Instructions
	// bool changed = this->deleteInstructions(f);
	return false;
	// Remove the following two lines before you write down your own codes
	// errs() << "Hello, \n" << *loop << "\n";
	// Iterate through the loop block. Need to figure out how to move something outside
	// a loop. The dataflow problem 'doDfa()' is to figure out what is loop invariant. 
	// We might have to add another doDfa() function which takes in 3 arguments - Loop , LoopInfo and LPPassManager
	// Unless we can access the LoopInfo directly and don't need to pass it.
	// Instruction* toDelete;
	// Instruction* toDelete1;
	// std::unordered_set<llvm::Instruction*> setTemp;
	// for (Loop::block_iterator bbItr = loop->block_begin(); bbItr != loop->block_end(); ++bbItr)
	// {
	// 	if (loopInfo.getLoopFor(*bbItr) == loop)
	// 	{
	// 		errs() << (*bbItr)->getName() << "\n";
	// 		// for (auto instItr = (*bbItr)->begin())
	// 		for (auto& inst : *(*bbItr))
	// 		{
	// 			errs() << "Iterating over instruction : " << inst.getName() << " \n";
	// 			if (inst.getName().str() == "mul")
	// 			{
	// 				errs() << "Inside If \n";
	// 				toDelete = &inst;
	// 				toDelete1 = &inst;
	// 				setTemp.insert(&inst);
	// 				errs() << " size : " << setTemp.size() << " \n";
	// 				setTemp.insert(&inst);
	// 				errs() << " size again: " << setTemp.size() << " \n";
	// 				// inst.moveBefore(loop->getLoopPreheader()->getTerminator());
	// 			}
	// 		}
	// 	}
	// }
	// toDelete->moveBefore(loop->getLoopPreheader()->getTerminator());
	// return false;
}

void LicmPass::getAnalysisUsage(AnalysisUsage &AU) const
{
	AU.addRequired<LoopInfo>();
	AU.setPreservesCFG();
}

char LicmPass::ID = 0;
static RegisterPass<LicmPass> X("licm-pass", "Loop invariant code motion for LLVM top-level vars");
