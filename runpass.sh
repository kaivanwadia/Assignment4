#!/bin/bash
clang -emit-llvm -c Output/$1.c -o Output/$1.bc
opt -mem2reg Output/$1.bc -o Output/$1.bc
make clean
make
opt -mergereturn -instnamer -load ./$2.so -disable-output -$2 ./Output/$1.bc
llvm-dis Output/$1.bc -o Output/$1.ll