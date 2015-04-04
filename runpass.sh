#!/bin/bash
clang -emit-llvm -c $1.c -o $1.bc
opt -mem2reg $1.bc -o $1.bc
make clean
make $2
opt -mergereturn -instnamer -load ./$2.so -disable-output -$2 ./$1.bc
llvm-dis $1.bc -o $1.ll