#ifndef CS380C_ASSIGNMENT4_MEET_H
#define CS380C_ASSIGNMENT4_MEET_H

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CFG.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Instructions.h>
#include "DFAFramework.h"
#include "Hasher.h"
#include "Equal.h"
#include <unordered_set>
#include <unordered_map>

using namespace llvm;

namespace cs380c
{
template<typename T, typename HasherType, typename EqualType>
class Meet
{
private:
	// using TypeSet = std::unordered_set<T, HasherType, EqualType>;
	// using DFAMap = std::unordered_map<const llvm::BasicBlock*, TypeSet>;
public:
	Meet() {}
	// Does the Meet operation on a BasicBlock. Returns an unordered set of the meet result.
	virtual bool doMeet(const llvm::BasicBlock* bb, std::unordered_map<const llvm::BasicBlock*, std::unordered_set<T, HasherType, EqualType>>& inMap, std::unordered_map<const llvm::BasicBlock*, std::unordered_set<T, HasherType, EqualType>>& outMap) = 0;
};

class DCEMeet: public Meet<llvm::StringRef, StringRefHash, StringRefEqual>
{
private:
public:
	DCEMeet() : Meet<llvm::StringRef, StringRefHash, StringRefEqual>() {}
	bool doMeet(const llvm::BasicBlock* bb, std::unordered_map<const llvm::BasicBlock*, std::unordered_set<llvm::StringRef, StringRefHash, StringRefEqual>>& inMap, std::unordered_map<const llvm::BasicBlock*, std::unordered_set<llvm::StringRef, StringRefHash, StringRefEqual>>& outMap)
	{
		bool updated = false;
		printf("into meet");
		return updated;
	}
};

}

#endif