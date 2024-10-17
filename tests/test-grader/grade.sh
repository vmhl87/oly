#!/bin/bash

g++ sol.cpp -o run -O2
ulimit -s unlimited

for file in *.in; do
	(time (timeout 5 ./run < $file > /tmp/run.out)) 2> /tmp/time.out
	out=$(echo $file | sed s/in/out/)
	case=$(echo $file | sed s/\.in//)
	time=$(cat /tmp/time.out | grep real | awk '{print $2}' | sed s/0m// | sed "s/\.//" | sed s/s/ms/)
	if [[ $(echo $time | sed s/ms//) -ge 5000 ]]; then
		echo -e "$case: \033[33mTLE\033[0m"
	else
		if [[ $time == "0000ms" ]]; then
			time="0ms"
		else
			time=$(echo $time | sed s/^0*//)
		fi
		if [[ $(diff /tmp/run.out $out) == "" ]]; then
			echo -e "$case: \033[32mAC\033[0m $time"
		else
			echo -e "$case: \033[31mWA\033[0m $time"
		fi
	fi
done
