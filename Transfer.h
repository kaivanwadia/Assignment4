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
		printf("In doTransfer of DCETransfer\n");

		TypeSet genSet;
		TypeSet killSet;
		for(auto instItr = bb->rbegin(); instItr != bb->rend(); instItr++)
		{
			// errs() << *instItr << "\n";
			// if terminator add to KILL
			StringRef lhs = (*instItr).getName();
			if(isa<TerminatorInst>(*instItr))
			{
				if (isa<ReturnInst>(*instItr))
				{
					for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
					{
						if (!(isa<Constant>(*opItr)) && !(isa<BasicBlock>(*opItr)))
						{
							killSet.insert((*opItr)->getName());
							 errs() << "Name : " << (*opItr)->getName() << "\n";
						}
					}
				}
				continue;
			}
			bool inKill = killSet.find(lhs) != killSet.end();
			// if LHS not in Kill then add LHS to GEN
			if(!inKill)
			{
				genSet.insert(lhs);
			}
			// if LHS is in (GEN U OUT) then add RHS to GEN
			bool inGen = genSet.find(lhs) != genSet.end();
			auto inOut = outMap[bb].find(lhs) != outMap[bb].end();
			if(inGen || inOut)
			{
				for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
				{
					if (!isa<Constant>(*opItr))
					{
						genSet.insert((*opItr)->getName());
					}
				}
			}
			// if LHS is in KILL then add RHS to KILL
			if(inKill)
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
		// FINAL FORMULA: IN = (OUT + GEN) - KILL
		TypeSet outVars = outMap[bb];
		TypeSet inVars;
		// errs() << "Kill Set : " << killSet.size() << "\n";
		// errs() << "Gen Set : " << genSet.size() << "\n";
		for (auto outVar : outVars)
		{
			if (killSet.count(outVar) == 0)
			{
				updated |= inVars.insert(outVar).second;
			}
		}
		for (auto genVar : genSet)
		{
			if (killSet.count(genVar) == 0)
			{
				updated |= inVars.insert(genVar).second;
			}
		}
		// errs() << "InVars Set : " << inVars.size() << "\n";
		inMap[bb] = inVars;
		return updated;
	}
};


class DCETransferPair: public Transfer<std::pair<StringRef, STATUS>, StringRefHashPair, StringRefEqualPair>
{
private:
public:
	using PairSet = std::pair<StringRef, STATUS>;
	DCETransferPair() : Transfer<PairSet, StringRefHashPair, StringRefEqualPair>() {}
	bool doTransfer(const llvm::BasicBlock* bb, DFAMap& inMap, DFAMap& outMap)
	{
		bool updated = false;
		printf("In doTransfer of DCETransfer\n");

		TypeSet genSet;
		TypeSet killSet;
		for(auto instItr = bb->rbegin(); instItr != bb->rend(); instItr++)
		{
			// errs() << *instItr << "\n";
			// if terminator add to KILL (AKA generate Liveness)
			StringRef lhs = (*instItr).getName();
			
			if(isa<TerminatorInst>(*instItr))
			{
				//if(isa<ReturnInst>(*instItr))
				{
					for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
					{
						if (!(isa<Constant>(*opItr)) && !(isa<BasicBlock>(*opItr)))
						{
							genSet.insert(PairSet((*opItr)->getName(), LIVE));
							 errs() << "Name : " << (*opItr)->getName() << "\n";
						}
					}
				}
			}

			// Find in genSet
			auto genItr = genSet.find(PairSet(lhs, FAINT));
			// Find in OutSet
			auto outItr = outMap[bb].find(PairSet(lhs, FAINT));
			// if found check if faint or live 
			bool foundOut = false;
			bool foundGen = false;
			if(outItr != outMap[bb].end())
			{
				if((*outItr).second == FAINT)
				{
					// do stuff on faint
				}
				else
				{
					// do stuff on live
					// add all the RHS stuff to Live as well
					for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
					{
						if (!isa<Constant>(*opItr))
						{
							genSet.insert(PairSet((*opItr)->getName(), LIVE));
						}
					}
				}
			}

			// Phi node case to add BB to live
			// if(isa<PHIInstruction>(*instItr))
			// {
			// 	if(genItr != genSet.end() || outItr != outMap[bb].end())
			// 	{

			// 	}
			// }


			// Check if it is in the gen set
			if(genItr != genSet.end())
			{
				if((*genItr).second == FAINT)
				{
					// do stuff on faint
				}
				else
				{
					// do stuff on live
					// insert the operands to the genSet as live varaibles
					for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
					{
						if (!isa<Constant>(*opItr))
						{
							genSet.insert(PairSet((*opItr)->getName(), LIVE));
						}
					}
				}
			}

			if(genItr == genSet.end() && outItr == outMap[bb].end())
			{
				genSet.insert(PairSet(lhs, FAINT));
			}

			/*if(isa<TerminatorInst>(*instItr))
			{
				if (isa<ReturnInst>(*instItr))
				{
					for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
					{
						if (!(isa<Constant>(*opItr)) && !(isa<BasicBlock>(*opItr)))
						{
							killSet.insert(PairSet((*opItr)->getName(), LIVE));
							 errs() << "Name : " << (*opItr)->getName() << "\n";
						}
					}
				}
				continue;
			}
			bool inKill = killSet.find(PairSet(lhs, LIVE)) != killSet.end();
			// if LHS not in Kill then add LHS to GEN
			if(!inKill)
			{
				genSet.insert(PairSet(lhs, FAINT));
			}*/
			// if LHS is in (GEN U OUT) then add RHS to GEN
			/*bool inGen = genSet.find(lhs) != genSet.end();
			auto inOut = outMap[bb].find(lhs) != outMap[bb].end();
			if(inGen || inOut)
			{
				for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
				{
					if (!isa<Constant>(*opItr))
					{
						genSet.insert((*opItr)->getName());
					}
				}
			}
			// if LHS is in KILL then add RHS to KILL
			if(inKill)
			{
				for (auto opItr = (*instItr).op_begin(); opItr != (*instItr).op_end(); ++opItr)
				{
					if (!isa<Constant>(*opItr))
					{
						killSet.insert((*opItr)->getName());
					}
				}
			}*/
		}
		// FINAL FORMULA: IN = (OUT + GEN) - KILL
		TypeSet outVars = outMap[bb];
		TypeSet inVars;
		// errs() << "Kill Set : " << killSet.size() << "\n";
		// errs() << "Gen Set : " << genSet.size() << "\n";
		for (auto outVar : outVars)
		{
			//if (killSet.count(outVar) == 0)
			{
				updated |= inVars.insert(outVar).second;
			}
		}
		for (auto genVar : genSet)
		{
			//if (killSet.count(genVar) == 0)
			{
				updated |= inVars.insert(genVar).second;
			}
		}
		// errs() << "InVars Set : " << inVars.size() << "\n";
		
		inMap[bb] = inVars;
		return updated;
	}
};
}

#endif