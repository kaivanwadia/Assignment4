#define DEBUG_TYPE "DCEPass"

#include "DCEPass.h"
#include "DataFlowAnnotator.h"
#include <unordered_set>
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace cs380c;
using namespace llvm;

STATISTIC(NumInstRemoved, "The # of dead instructions removed by DCEPass");

bool DCEPass::runOnFunction(Function& f)
{
	StringSet initialSet;
	populateInitialSet(initialSet, f);
	dfa->setInitialValues(initialSet);
	dfa->doDFA(f);
	DataFlowAnnotator<DCEPass> annotator(*this, errs());
	annotator.print(f);

	for (auto& bb : f)
	{
		std::vector<Instruction*> toBeDeleted;
		StringSet inFaintSet = this->getInValues(&bb);
		for (auto& inst : bb)
		{
			if (inFaintSet.count(inst.getName()) != 0)
			{
				toBeDeleted.push_back(&inst);
			}
		}
		for (int i = toBeDeleted.size() - 1; i>=0; i--)
		{
			Instruction* inst = toBeDeleted[i];
			errs() << "Deleting : " << inst->getName() << "\n";
			inst->eraseFromParent();
		}
	}
	annotator.print(f);	
	return true;
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
}

void DCEPass::getAnalysisUsage(AnalysisUsage &AU) const
{
	AU.setPreservesCFG();
}

char DCEPass::ID = 0;
static RegisterPass<DCEPass> X("dce-pass", "Faintness Analysis and dead code elimination for LLVM top-level vars");



