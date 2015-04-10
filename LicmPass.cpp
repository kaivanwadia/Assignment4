#define DEBUG_TYPE "LicmPass"

#include "LicmPass.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/DenseMap.h"
#include <unordered_set>
#include <queue>
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
	dfa->setTransferHelpers(loop);
	dfa->doDFA(loop, lpm);
	// Delete the instructions
	bool changed = this->deleteInstructions(loop);
	return changed;
}

bool LicmPass::deleteInstructions(llvm::Loop* loop)
{
	bool changed = false;
	std::unordered_map<int ,BasicBlock*> reversePostOrder;
	for (auto it = dfa->getPostOrderMap()->begin(); it != dfa->getPostOrderMap()->end(); ++it)
	{
		reversePostOrder[it->second] = it->first;
		DEBUG( errs() << it->second << " : " << it->first->getName() << "\n");
	}
	DEBUG( errs() << "Deleting Instructions\n");
	DEBUG( errs() << "reversePostOrder size : " << reversePostOrder.size() << "\n");
	DEBUG( errs() << "=============Start Hoisting================\n" );
	for (int i = reversePostOrder.size() - 1; i >= 0; i--)
	{
		BasicBlock* bb = reversePostOrder[i];
		if (loop->contains(bb))
		{
			std::queue<Instruction*> toBeHoisted;
			InstSet outInvariant = this->getInValues(bb);
			for (auto& inst : *bb)
			{
				if (outInvariant.count(&inst) != 0)
				{
					toBeHoisted.push(&inst);
					changed = true;
				}
			}
			while (!toBeHoisted.empty())
			{
				Instruction* toHoist = toBeHoisted.front();
				toBeHoisted.pop();
				DEBUG (errs() << "Hoisting : " << toHoist->getName() << "\t" << "Type : " );
				DEBUG (toHoist->getType()->print(errs()) );
				DEBUG (errs() <<"\n" );
				toHoist->moveBefore(loop->getLoopPreheader()->getTerminator());
				NumInstHoisted++;
			}
		}
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
