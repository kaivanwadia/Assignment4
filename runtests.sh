#!/bin/bash
rm -f $1*.bc $1*.ll
for i in $1*.c
do
	clang -emit-llvm -c $i -o ${i%.c}.bc
	opt -mem2reg ${i%.c}.bc -o ${i%.c}.bc
done

make clean
stats=""
if [[ $* == *-stats* ]]
	then
	stats="-stats"
fi

debug=""
if [[ $* == *-debug* ]]
then
	debug="-debug"
	echo "adding debug flag"
fi

if [ "$2" == "licm-pass" ]
then
	make $2
	for i in $1*.bc
	do
		echo "====================== $i ==================="
		opt $debug $stats -loop-simplify -mergereturn -instnamer -load ./$2.so -$2 $i -o ${i%.bc}_Opt.bc
		llvm-dis $i -o ${i%.bc}.ll

		if [ "$3" == "test" ]
		then
			echo "TEST BEGIN"
			clang $i -o temp
			./temp > ${i%.bc}_orig
			clang ${i%.bc}_Opt.bc -o temp
			./temp > ${i%.bc}_opt
			rm -f temp
			diff ${i%.bc}_orig ${i%.bc}_orig
			echo "TEST DONE"
		fi		
		echo "===================== END ==================="
	done
fi

if [ "$2" == "dce-pass" ]
then
	make $2
	for i in $1*.bc
	do
		echo "====================== $i ==================="
		opt $debug $stats -mergereturn -instnamer -load ./$2.so -$2 $i -o ${i%.bc}_Opt.bc
		llvm-dis $i -o ${i%.bc}.ll

		if [ "$3" == "test" ]
		then
			echo "TEST BEGIN"
			clang $i -o temp
			./temp #> ${i%.bc}_orig
			clang ${i%.bc}_Opt.bc -o temp
			./temp #> ${i%.bc}_opt
			rm -f temp
			diff ${i%.bc}_orig ${i%.bc}_orig
			echo "TEST DONE"
		fi		
		echo "===================== END ==================="
	done
fi