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
	using StringSet = std::unordered_set<StringRef, StringRefHash, StringRefEqual>;
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
		StringSet intersectedSet;
		for(auto bbOuter = succ_begin(bb); bbOuter != succ_end(bb); bbOuter++)
		{
			auto outerVariables = inMap[*bbOuter];
			for(auto const variable : outerVariables)
			{
				bool present = true;
				for(auto bbItr = succ_begin(bb); bbItr != succ_end(bb); bbItr++)
				{
					if(bbOuter == bbIter) // Same basic block just continue
						continue;

					auto checkPtr = inMap[*bbItr].find(variable);
					if(checkPtr == inMap[*bbItr].end())
					{
						present = false;
					}
				}
				if(present)
				{
					intersectedSet.insert(variable);
				}
			}
		}

		if(intersectedSet.size() != bbVariables.size())
		{
			updated = true;
		}
		else
		{
			updated = false;
			for(auto variable : bbVariables)
			{
				auto checkPtr = intersectedSet.find(bbVariables);
				if(checkPtr == intersectedSet.end())
				{
					updated = true;
				}
			}
		}

		bbVariables = intersectedSet;
		
		return updated;
	}
};

}

#endif