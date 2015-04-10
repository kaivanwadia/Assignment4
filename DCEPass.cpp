#define DEBUG_TYPE "DCEPass"

#include "DCEPass.h"
#include "DataFlowAnnotator.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/IR/Constants.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>

using namespace cs380c;
using namespace llvm;

STATISTIC(NumInstRemoved, "The # of dead instructions removed by DCEPass");

bool DCEPass::runOnFunction(Function& f)
{
	StringSet initialSet;
	populateInitialSet(initialSet, f);
	delete dfa;
	dfa = new DFAFramework<StringRef, StringRefHash, StringRefEqual>(false, new DCEMeet(), new DCETransfer());
	dfa->setInitialValues(initialSet);
	dfa->doDFA(f);
	DataFlowAnnotator<DCEPass> annotator(*this, errs());
	DEBUG( annotator.print(f) );

	// Delete Instructions
	bool changed = this->deleteInstructions(f);
	DEBUG( annotator.print(f) );
	return true;
}

bool DCEPass::deleteInstructions(Function& f)
{
	bool changed = false;
	DEBUG(errs() << "=============Start Deletion================\n");
	for (auto& bb : f)
	{
		std::vector<Instruction*> toBeDeleted;
		StringSet inFaintSet = this->getInValues(&bb);
		for (auto& inst : bb)
		{
			if (inFaintSet.count(inst.getName()) != 0)
			{
				toBeDeleted.push_back(&inst);
				changed = true;
			}
		}
		for (int i = toBeDeleted.size() - 1; i>=0; i--)
		{
			Instruction* inst = toBeDeleted[i];
			DEBUG (errs() << "Deleting : " << inst->getName() << "\t" << "Type : ");
			DEBUG (inst->getType()->print(errs()) );
			DEBUG (errs() <<"\n" );
			if (isa<PHINode>(inst))
			{
				PHINode* phiInst = dyn_cast<PHINode>(inst);
				for (int operandNo = phiInst->getNumIncomingValues() -1; operandNo >= 0; operandNo--)
				{
					phiInst->removeIncomingValue(operandNo, true);
				}
				NumInstRemoved++;
			}
			else
			{
				UndefValue* replacement = UndefValue::get(inst->getType());
				inst->replaceAllUsesWith(replacement);
				inst->eraseFromParent();
				NumInstRemoved++;
			}
		}
		toBeDeleted.clear();
	}
	DEBUG(errs() << "=============End Deletion================\n");
	return changed;
}

void DCEPass::populateInitialSet(StringSet& set, Function& f)
{
	for(auto& bb : f)
	{
		for(auto& inst : bb)
		{
			StringRef lhs = inst.getName();
			if(lhs.str() != "")
			{
				set.insert(lhs);
			}
		}
	}
	for (auto itr = f.getArgumentList().begin(); itr != f.getArgumentList().end(); ++itr)
	{
		set.insert((*itr).getName());
	}
}

void DCEPass::getAnalysisUsage(AnalysisUsage &AU) const
{
	AU.setPreservesCFG();
}

char DCEPass::ID = 0;
static RegisterPass<DCEPass> X("dce-pass", "Faintness Analysis and dead code elimination for LLVM top-level vars");



