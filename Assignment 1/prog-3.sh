#!/bin/bash

# 3. to check the given number is odd or even.

echo "Enter a number"
read num

if [[ `expr $num % 2` -eq 0 ]]; then
	echo "Even"
else
	echo "Odd"
fi
