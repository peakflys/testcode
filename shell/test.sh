#!/bin/bash
PID=`pgrep $1`
echo $PID
if [ -n $PID ]; then
	echo "PID is $PID"
else
	echo "PID is null"
fi

if [ -z $PID ]; then
	echo "PID is null"
else
	echo "PID is $PID"
fi

if [ $PID -ne 0 ]; then
	echo "PID is $PID"
else
	echo "PID is null"
fi

