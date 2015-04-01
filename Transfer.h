#ifndef CS380C_ASSIGNMENT4_TRANSFER_H
#define CS380C_ASSIGNMENT4_TRANSFER_H

#include <llvm/IR/BasicBlock.h>
#include "DFAFramework.h"
#include <unordered_set>
#include <unordered_map>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Instructions.h>
#include "Hasher.h"
#include "Equal.h"

using namespace llvm;
namespace cs380c
{

template <typename T, typename HasherType, typename EqualType>
class Transfer
{
private:
public:
	using TypeSet = std::unordered_set<T, HasherType, EqualType>;
	using DFAMap = std::unordered_map<const llvm::BasicBlock*, TypeSet>;
	Transfer() {}
	// Does the Transfer operation on a BasicBlock. Returns a bool of the transfer result.
	virtual bool doTransfer(const llvm::BasicBlock* bb, DFAMap& inMap, DFAMap& outMap) = 0;
};

class DCETransfer: public Transfer<llvm::StringRef, StringRefHash, StringRefEqual>
{
private:
public:
	DCETransfer() : Transfer<llvm::StringRef, StringRefHash, StringRefEqual>() {}
	bool doTransfer(const llvm::BasicBlock* bb, DFAMap& inMap, DFAMap& outMap)
	{
		bool updated = false;
		printf("into transfer\n");
		return updated;
	}
};
}

#endif