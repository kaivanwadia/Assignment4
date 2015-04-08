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
template<typename T, typename HasherType = std::hash<T>, typename EqualType = std::equal_to<T> >
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

class LICMMeet: public Meet<llvm::Instruction*>
{
public:
	using InstSet = std::unordered_set<Instruction*, std::hash<llvm::Instruction*>, std::equal_to<llvm::Instruction*> >;
	LICMMeet() : Meet<llvm::Instruction*>() {}

	bool doMeet( const llvm::BasicBlock* bb, DFAMap& inMap, DFAMap& outMap)
	{
		printf("In doMeet of LICMMeet\n");

		bool updated = false;
		auto itr = inMap.find(bb);
		if(itr == inMap.end())
		{
			updated = true;
			itr = inMap.insert(std::make_pair(bb, InstSet())).first;	
		}
		auto& instSet = itr->second;
		InstSet newSet;
		for(auto bbItr = pred_begin(bb); bbItr != pred_end(bb); bbItr++)
		{
			auto predItr = outMap.find(*bbItr);
			if(predItr == outMap.end())
			{
				continue;
			}
			auto predVars = outMap[*bbItr];
			// errs() << "PredVars size : " << predVars.size() << "\n";
			for(Instruction* inst : predVars)
			{
				newSet.insert(inst);
			}
		}
		// errs() << "NewSet size : " << newSet.size() << "\n";
		if(newSet.size() != instSet.size())
		{
			updated |= true;
		}
		else
		{
			for(auto variable : instSet)
			{
				if(newSet.count(variable) == 0)
				{
					updated |= true;
				}
			}
		}
		instSet = newSet;
		return updated;
	}

};

class DCEMeet: public Meet<llvm::StringRef, StringRefHash, StringRefEqual>
{
private:
public:
	using StringSet = std::unordered_set<StringRef, StringRefHash, StringRefEqual>;
	DCEMeet() : Meet<llvm::StringRef, StringRefHash, StringRefEqual>() {}
	bool doMeet(const llvm::BasicBlock* bb, DFAMap& inMap, DFAMap& outMap)
	{
		printf("In doMeet of DCEMeet\n");
		bool updated = false;
		if (bb->getTerminator()->getNumSuccessors() == 0)
		{
			return updated;
		}
		auto itr = outMap.find(bb);
		if(itr == outMap.end())
		{
			updated |= true;
			itr = outMap.insert(std::make_pair(bb, TypeSet())).first;
		}
		auto& bbVariables = itr->second;
		StringSet intersectedSet;
		for(auto bbOuter = succ_begin(bb); bbOuter != succ_end(bb); bbOuter++)
		{
			if (inMap.find(*bbOuter) == inMap.end())
			{
				// errs() << "No map for BB Outer : " << (*bbOuter)->getName() << "\n";
				continue;
			}
			auto outerVariables = inMap[*bbOuter];
			for(auto const variable : outerVariables)
			{
				bool present = true;
				for(auto bbInner = succ_begin(bb); bbInner != succ_end(bb); bbInner++)
				{
					if(bbOuter == bbInner) // Same basic block just continue
					{
						continue;
					}
					if (inMap.find(*bbInner) == inMap.end())
					{
						// errs() << "No map for BB Inner : " << (*bbInner)->getName() << "\n";
						continue;
					}
					if (inMap[*bbInner].count(variable) == 0) // Could not find variable. Don't put in intersectedSet
					{
						present = false;
					}
				}
				if(present)
				{
					// printf("%s :added ", variable.str().c_str());
					intersectedSet.insert(variable);
				}
			}
		}
		if(intersectedSet.size() != bbVariables.size())
		{
			updated |= true;
		}
		else
		{
			for(auto variable : bbVariables)
			{
				if(intersectedSet.count(variable) == 0)
				{
					updated |= true;
				}
			}
		}
		bbVariables = intersectedSet;
		return updated;
	}
};

}

#endif