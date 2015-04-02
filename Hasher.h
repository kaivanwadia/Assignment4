#ifndef CS380C_ASSIGNMENT4_HASHER_H
#define CS380C_ASSIGNMENT4_HASHER_H

using namespace llvm;

namespace cs380c
{
template<typename T>
class Hasher
{
public:
	virtual size_t operator() (const T &element) const = 0;
};
class StringRefHashPair : Hasher<std::pair<llvm::StringRef, STATUS>>
{
public:
	size_t operator() (const std::pair<llvm::StringRef, STATUS> &element) const
	{
		std::hash<std::string> stringHashFn;
		return stringHashFn(element.first.str());
	}
};


class StringRefHash : Hasher<llvm::StringRef>
{
public:
	size_t operator() (const llvm::StringRef &element) const
	{
		std::hash<std::string> stringHashFn;
		return stringHashFn(element.str());
	}
};
}
#endif