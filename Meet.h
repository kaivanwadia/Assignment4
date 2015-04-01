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
public:
	using TypeSet = std::unordered_set<T, HasherType, EqualType>;
	using DFAMap = std::unordered_map<const llvm::BasicBlock*, TypeSet>;
	Meet() {}
	// Does the Meet operation on a BasicBlock. Returns an unordered set of the meet result.
	virtual bool doMeet(const llvm::BasicBlock* bb, DFAMap& inMap, DFAMap& outMap) = 0;
};

class DCEMeet: public Meet<llvm::StringRef, StringRefHash, StringRefEqual>
{
private:
public:
	DCEMeet() : Meet<llvm::StringRef, StringRefHash, StringRefEqual>() {}
	bool doMeet(const llvm::BasicBlock* bb, DFAMap& inMap, DFAMap& outMap)
	{
		bool updated = false;
		printf("In doMeet of DCEMeet\n");
		auto itr = outMap.find(bb);
		if(itr == outMap.end())
		{
			updated = true;
			itr = outMap.insert(std::make_pair(bb, TypeSet())).first;
		}

		auto& bbVariables = itr->second;
		for(auto bbItr = succ_begin(bb); bbItr != succ_end(bb); bbItr++)
		{
			auto succVariables = inMap[*bbItr];
			for(auto const variable : succVariables)
			{
				updated |= bbVariables.insert(variable).second;
			}
		}
		return updated;
	}
};

}

#endif