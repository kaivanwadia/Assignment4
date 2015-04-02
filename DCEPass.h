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
	using PairSet = std::pair<StringRef, STATUS>;
	DFAFramework<PairSet, StringRefHashPair, StringRefEqualPair>* dfa;
	DCEPass() : llvm::FunctionPass(ID) {
		dfa = new DFAFramework<PairSet, StringRefHashPair, StringRefEqualPair>(false, new DCEMeetPair(), new DCETransferPair());
	}

	bool runOnFunction(llvm::Function&);

	const std::unordered_set<PairSet, StringRefHashPair, StringRefEqualPair>& getInValues(const llvm::BasicBlock* bb) const {
		return dfa->getInValues(bb);
	}
	const std::unordered_set<PairSet, StringRefHashPair, StringRefEqualPair>& getOutValues(const llvm::BasicBlock* bb) const {
		return dfa->getOutValues(bb);
	}

	void getAnalysisUsage(llvm::AnalysisUsage &AU) const;
};

}

#endif