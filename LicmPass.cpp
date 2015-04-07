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
	InstSet initialSet;
	dfa->setInitialValues(initialSet);
	LoopInfo& loopInfo = getAnalysis<LoopInfo>();
	DominatorTreeWrapperPass& dominatorInfo = getAnalysis<DominatorTreeWrapperPass>();
	dfa->setDominatorTree(&dominatorInfo);
	dfa->doDFA(loop, lpm, loopInfo);
	// errs() << "Contained : " << lpm.getNumContainedPasses() << "\n";
	// DenseMap<AnalysisID, Pass*>* tempMap = lpm.getAvailableAnalysis();
	// for (auto key = tempMap->begin(); key != tempMap->end(); ++key)
	// {
	// 	errs() << "In loop \n";
	// 	// std::cout << (*key) << "\n";
	// 	// errs() << (*key) << "\n";
	// 	// lookupPassInfo(*key);
	// 	// errs() << "sasssss : " << lookupPassInfo(*key) << "\n";
	// 	// errs() << "Sadsad : " << tempMap->lookup(LoopInfo::ID) << "\n";
	// }
	// Delete Instructions
	// bool changed = this->deleteInstructions(f);
	// return false;
	// errs() << "Hello, \n" << *loop << "\n";

	// Remove the following two lines before you write down your own codes
	// Iterate through the loop block. Need to figure out how to move something outside
	// a loop. The dataflow problem 'doDfa()' is to figure out what is loop invariant. 
	// We might have to add another doDfa() function which takes in 3 arguments - Loop , LoopInfo and LPPassManager
	// Unless we can access the LoopInfo directly and don't need to pass it.
	// for (Loop::block_iterator bbItr = loop->block_begin(); bbItr != loop->block_end(); ++bbItr)
	// {
	// 	if (loopInfo.getLoopFor(*bbItr) == loop)
	// 	{
	// 		errs() << "Basic block : " << (*bbItr)->getName() << "\n";
	// 		for (auto& inst : *(*bbItr))
	// 		{
	// 			errs() << "Iterating over instruction : " << inst.getName() << " \n";
	// 			for (auto opItr = inst.op_begin(); opItr != inst.op_end(); ++opItr)
	// 			{
	// 				if (!(isa<Constant>(*opItr)) && !(isa<BasicBlock>(*opItr)))
	// 				{
	// 					errs() << "Operand : " << (*opItr)->getName() << "\n";
	// 					errs() << "Passed dynamic cast\n";
	// 					if (isa<Argument>(*opItr))
	// 					{
	// 						errs() << "Argument \n";
	// 						errs() << "Op BasicBlock : Outside function \n";
	// 						errs() << "Not Contained In loop \n";
	// 						continue;
	// 					}
	// 					Instruction* instDef = dyn_cast<Instruction>(*opItr);
	// 					BasicBlock* bb = instDef->getParent();
	// 					errs() << "Op BasicBlock : " << bb->getName() << "\n";
	// 					// errs() << "Op BasicBlock : " << bb->getName() << "\n";
	// 					if (loop->contains((instDef)))
	// 					{
	// 						errs() << "Contained In loop \n";
	// 					}
	// 					else
	// 					{
	// 						errs() << "Not Contained In loop \n";
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// toDelete->moveBefore(loop->getLoopPreheader()->getTerminator());
	return false;
}

void LicmPass::getAnalysisUsage(AnalysisUsage &AU) const
{
	AU.addRequired<LoopInfo>();
	AU.addRequired<DominatorTreeWrapperPass>();
	AU.setPreservesCFG();
}

char LicmPass::ID = 0;
static RegisterPass<LicmPass> X("licm-pass", "Loop invariant code motion for LLVM top-level vars");
