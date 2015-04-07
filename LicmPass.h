#ifndef CS380C_ASSIGNMENT4_LICM_H
#define CS380C_ASSIGNMENT4_LICM_H

#include "llvm/Analysis/LoopPass.h"
#include "DFAFramework.h"

namespace cs380c
{

class LicmPass: public llvm::LoopPass
{
private:
	// Private fields go here
public:
	static char ID;
	using InstSet = std::unordered_set<llvm::Instruction*, std::hash<llvm::Instruction*>, std::equal_to<llvm::Instruction*>>;
	DFAFramework<llvm::Instruction*>* dfa;
	LicmPass() : llvm::LoopPass(ID) {
		dfa = new DFAFramework<llvm::Instruction*>(true, new LICMMeet(), new LICMTransfer());
	}

	bool runOnLoop(llvm::Loop*, llvm::LPPassManager&);

	void getAnalysisUsage(llvm::AnalysisUsage &AU) const;
};

}

#endif
