#!/bin/bash

# 1. to find profit or loss given the cost price and selling price.

echo "Enter cost price "
read cp
echo "Enter selling price"
read sp

if [[ $cp -eq $sp ]]; then
	echo "No Profit"
elif [[ $cp -le $sp ]]; then
	echo "Profit of `expr $sp - $cp`"
else
	echo "Loss of `expr $cp - $sp`"
fi
