#ifndef CS380C_ASSIGNMENT4_DCEPASS_H
#define CS380C_ASSIGNMENT4_DCEPASS_H


#include "DFAFramework.h"
#include "llvm/Pass.h"



namespace cs380c
{

class DCEPass: public llvm::FunctionPass
{
private:
	// Private fields go here
public:
	static char ID;
	DFAFramework<llvm::StringRef, StringRefHash, StringRefEqual>* dfa;
	DCEPass() : llvm::FunctionPass(ID) {
		dfa = new DFAFramework<llvm::StringRef, StringRefHash, StringRefEqual>(false, new DCEMeet(), new DCETransfer());
	}

	bool runOnFunction(llvm::Function&);

	void getAnalysisUsage(llvm::AnalysisUsage &AU) const;
};

}

#endif