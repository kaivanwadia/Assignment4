#ifndef CS380C_ASSIGNMENT4_DCEPASS_H
#define CS380C_ASSIGNMENT4_DCEPASS_H

#include "llvm/Pass.h"

namespace cs380c
{

class DCEPass: public llvm::FunctionPass
{
private:
	// Private fields go here
public:
	static char ID;
	DCEPass() : llvm::FunctionPass(ID) {}

	bool runOnFunction(llvm::Function&);

	void getAnalysisUsage(llvm::AnalysisUsage &AU) const;
};

}

#endif