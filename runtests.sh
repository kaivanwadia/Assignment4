#!/bin/bash
rm -f $1*.bc $1*.ll
for i in $1*.c
do
	clang -emit-llvm -c $i -o ${i%.c}.bc
	opt -mem2reg ${i%.c}.bc -o ${i%.c}.bc
done

make clean

if [ "$2" == "licm-pass" ]
then
	make $2
	for i in $1*.bc
	do
		echo "====================== $i ==================="
		opt -stats -loop-simplify -mergereturn -instnamer -load ./$2.so -$2 $i -o $i
		#llvm-dis $i -o ${i%.bc}.ll
	done
fi
