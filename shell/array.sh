#!/bin/bash
array=("10" "20" "30" "40" "50" "60")
for i in ${array[@]}; do
	echo $i
done

echo "it's ok"
for i in ${!array[@]}; do
	echo $i 
done

echo "it's ok"
for (( i=${#array[@]}-1; i>=0; --i)); do
	echo ${array[$i]}
done
