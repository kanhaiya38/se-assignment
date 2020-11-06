#!/bin/bash

# 7.find the largest of 3 numbers.

echo "Enter first number"
read first
echo "Enter second number"
read second
echo "Enter third number"
read third

max=$first
if (( $max < $second )); then
	max=$second
fi
if (( $max < $third )); then
	max=$third
fi
echo "Largest Number is $max"
