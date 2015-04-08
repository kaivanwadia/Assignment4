#define DEBUG_TYPE "LicmPass"

#include "LicmPass.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/DenseMap.h"
#include <unordered_set>
#include "Equal.h"
#include <iostream>

using namespace cs380c;
using namespace llvm;

STATISTIC(NumInstHoisted, "The # of instructions hoisted by LicmPass");

bool LicmPass::runOnLoop(llvm::Loop* loop, llvm::LPPassManager& lpm)
{
	DEBUG( errs() << "In runOnLoop\n" );
	InstSet initialSet;
	delete dfa;
	dfa = new DFAFramework<llvm::Instruction*>(true, new LICMMeet(), new LICMTransfer());
	dfa->setInitialValues(initialSet);
	// LoopInfo& loopInfo = getAnalysis<LoopInfo>();
	DominatorTreeWrapperPass& dominatorInfo = getAnalysis<DominatorTreeWrapperPass>();
	dfa->setTransferHelpers(&dominatorInfo, loop);
	dfa->doDFA(loop, lpm);
	// Delete the instructions
	bool changed = this->deleteInstructions(loop);
	return changed;
}

bool LicmPass::deleteInstructions(llvm::Loop* loop)
{
	bool changed = false;
	// std::unordered_map<int ,BasicBlock*> reversePostOrder;
	// for (auto it = dfa->getPostOrderMap()->begin(); it != dfa->getPostOrderMap()->end(); ++it)
	// {
	// 	reversePostOrder[it->second]
	// }
	DEBUG( errs() << "=============Start Hoisting================\n" );
	for (Loop::block_iterator bbItr = loop->block_begin(); bbItr != loop->block_end(); ++bbItr)
	{
		std::vector<Instruction*> toBeHoisted;
		InstSet outInvariant = this->getInValues((*bbItr));
		for (auto& inst : *(*bbItr))
		{
			if (outInvariant.count(&inst) != 0)
			{
				toBeHoisted.push_back(&inst);
				changed = true;
			}
		}
		for (int i = toBeHoisted.size() - 1; i>=0; i--)
		{
			Instruction* toHoist = toBeHoisted[i];
			DEBUG (errs() << "Hoisting : " << toHoist->getName() << "\t" << "Type : " );
			DEBUG (toHoist->getType()->print(errs()) );
			DEBUG (errs() <<"\n" );
			toHoist->moveBefore(loop->getLoopPreheader()->getTerminator());
			NumInstHoisted++;
		}
		toBeHoisted.clear();
	}
	DEBUG( errs() << "=============End Hoisting================\n" );
	return changed;
}

void LicmPass::getAnalysisUsage(AnalysisUsage &AU) const
{
	AU.addRequired<LoopInfo>();
	AU.addRequired<DominatorTreeWrapperPass>();
	AU.setPreservesCFG();
}

char LicmPass::ID = 0;
static RegisterPass<LicmPass> X("licm-pass", "Loop invariant code motion for LLVM top-level vars");
