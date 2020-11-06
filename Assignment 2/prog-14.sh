#!/bin/bash

# 14. to find the factorial of a number.

echo "Enter a number to find its factorial"
read num;

ans=1

while (( $num > 0 )); do
	ans=$(bc <<< "$ans * $num")
	(( num-- ))
done

echo "$ans"
