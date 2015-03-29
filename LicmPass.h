#ifndef CS380C_ASSIGNMENT4_LICM_H
#define CS380C_ASSIGNMENT4_LICM_H

#include "llvm/Analysis/LoopPass.h"

namespace cs380c
{

class LicmPass: public llvm::LoopPass
{
private:
	// Private fields go here
public:
	static char ID;
	// Just making edits
	LicmPass() : llvm::LoopPass(ID) {}

	bool runOnLoop(llvm::Loop*, llvm::LPPassManager&);

	void getAnalysisUsage(llvm::AnalysisUsage &AU) const;
};

}

#endif
