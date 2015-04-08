#!/bin/bash
clang -emit-llvm -c $1.c -o $1.bc
opt -mem2reg $1.bc -o $1.bc
make clean
debug=""
if [[ $* == *-debug* ]]
then
	debug="-debug"
fi
if [ "$2" == "licm-pass" ]
then
	make $2
	opt -stats -loop-simplify $debug -mergereturn -instnamer -load ./$2.so -$2 ./$1.bc -o ./$1_Opt.bc
elif [ "$2" == "dce-pass" ]
then
	make $2
	opt -stats $debug -mergereturn -instnamer -load ./$2.so -$2 ./$1.bc -o ./$1_Opt.bc
else
	make
	opt -stats $debug -loop-simplify -mergereturn -instnamer -load ./licm-pass.so -licm-pass ./$1.bc -o ./$1_Opt.bc
	opt -stats $debug -mergereturn -instnamer -load ./dce-pass.so -dce-pass ./$1_Opt.bc -o ./$1_Opt.bc
fi
llvm-dis $1.bc -o $1.ll
llvm-dis $1_Opt.bc -o $1_Opt.ll
if [ "$3" == "test" ]
then
	echo "TEST BEGIN"
	clang $1.bc -o temp
	./temp > origOut
	clang $1_Opt.bc -o temp
	./temp > optOut
	rm -f temp
	diff origOut optOut
	echo "TEST DONE"
fi