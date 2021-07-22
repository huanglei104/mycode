#!/bin/bash

if [ $# -ne 1 ];then
	echo "argument error"
	exit;
fi

if [ -d "$1" ];then
	for f in $(ls ${1});do
		echo $f
	done
fi

if [ -z "" -o -n 'c' ];then
	echo 'aaaaa'
fi

abc=$(echo ahello| awk 'NF < 100 {print}')
echo ${abc}

