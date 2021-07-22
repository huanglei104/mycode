#!/bin/bash

echo "脚本名称：" $0
echo "参数：" $*
echo "参数个数：" $#

name="huanglei"

[[ $# == 10 ]]

echo ${#name}
var=$[1+2]
var2=$[var * 2]
echo $var2

array=(xixi haha baba gaga)
echo "array elements:" ${#array[@]}
echo "array elements:" ${#array[*]}

for i in ${array[*]};do
	echo $i
done
