#!/bin/bash

# 16. to print a pyramid of numbers.

echo "Enter height of pyramid"
read height

for (( i = 0; i < $height; i++)); do
	for (( j = i; j < $height - 1; j++ )); do
		echo -n " "
	done
	echo -n "1"
	for ((j = 0; j < 2 * i; j++ )); do
		echo -n "1"
	done
	echo
done
