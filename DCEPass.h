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
	using StringSet = std::unordered_set<StringRef, StringRefHash, StringRefEqual>;
	DFAFramework<StringRef, StringRefHash, StringRefEqual>* dfa;
	DCEPass() : llvm::FunctionPass(ID) {
		dfa = new DFAFramework<StringRef, StringRefHash, StringRefEqual>(false, new DCEMeet(), new DCETransfer());
	}

	bool runOnFunction(llvm::Function&);

	void populateInitialSet(StringSet& set, Function &f);

	const std::unordered_set<StringRef, StringRefHash, StringRefEqual>& getInValues(const llvm::BasicBlock* bb) const {
		return dfa->getInValues(bb);
	}
	const std::unordered_set<StringRef, StringRefHash, StringRefEqual>& getOutValues(const llvm::BasicBlock* bb) const {
		return dfa->getOutValues(bb);
	}

	void getAnalysisUsage(llvm::AnalysisUsage &AU) const;
};

}

#endif