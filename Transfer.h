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

template <typename T, typename HasherType = std::hash<T>, typename EqualType = std::equal_to<T> >
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

class LICMTransfer : public Transfer<llvm::Instruction*>
{
public:
	using InstSet = std::unordered_set<llvm::Instruction*, std::hash<llvm::Instruction*>, std::equal_to<llvm::Instruction*>>;
	LICMTransfer() : Transfer<llvm::Instruction*>() {}

	bool doTransfer( const llvm::BasicBlock* bb, DFAMap& inMap, DFAMap& outMap)
	{
		return false;
	}
};

class DCETransfer: public Transfer<llvm::StringRef, StringRefHash, StringRefEqual>
{
private:
public:
	DCETransfer() : Transfer<llvm::StringRef, StringRefHash, StringRefEqual>() {}
	bool doTransfer(const llvm::BasicBlock* bb, DFAMap& inMap, DFAMap& outMap)
	{
		bool updated = false;
		printf("In doTransfer of DCETransfer\n");

		TypeSet genSet;
		TypeSet killSet;
		TypeSet outSet = outMap[bb];
		for(auto instItr = bb->rbegin(); instItr != bb->rend(); instItr++)
		{
			// If a terminator instruction then add to kill set
			if(isa<TerminatorInst>(*instItr))
			{
				for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
				{
					if (!(isa<Constant>(*opItr)) && !(isa<BasicBlock>(*opItr)))
					{
						killSet.insert((*opItr)->getName());
						// errs() << "Name : " << (*opItr)->getName() << "\n";
					}
				}
				continue;
			}
			StringRef lhs = (*instItr).getName();
			bool inOutSet = outSet.count(lhs) != 0? true : false;
			bool inKillSet = killSet.count(lhs) != 0? true : false;
			// If lhs is not in outSet then add rhs to kill
			if (!inOutSet || inKillSet)
			{
				for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
				{
					if (!isa<Constant>(*opItr))
					{
						killSet.insert((*opItr)->getName());
					}
				}
			}
		}
		TypeSet inVars;
		// errs() << "Kill Set : " << killSet.size() << "\n";
		// errs() << "Gen Set : " << genSet.size() << "\n";
		for (auto outVar : outSet)
		{
			if (killSet.count(outVar) == 0)
			{
				updated |= inVars.insert(outVar).second;
			}
		}
		// errs() << "InVars Set : " << inVars.size() << "\n";
		inMap[bb] = inVars;
		return updated;
	}
};
}

#endif