#!/bin/bash
clang -emit-llvm -c $1.c -o $1.bc
opt -mem2reg $1.bc -o $1.bc
make clean
make $2
if [ "$2" == "licm-pass" ]
then
	opt -stats -loop-simplify -mergereturn -instnamer -load ./$2.so -$2 ./$1.bc -o ./$1_Opt.bc
else
	opt -stats -mergereturn -instnamer -load ./$2.so -$2 ./$1.bc -o ./$1_Opt.bc
fi
llvm-dis $1.bc -o $1.ll
llvm-dis $1_Opt.bc -o $1_Opt.ll