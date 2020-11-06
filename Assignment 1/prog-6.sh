#!/bin/bash

# 6. simple calculator for basic arithmetic operations.
# (take operand-1, operator and operand-2 from user as input)

echo "Enter first operand"
read operand_1
echo "Enter operator"
read operator
echo "Enter second operand"
read operand_2
echo "Result: $(bc <<< "$operand_1 $operator $operand_2")"
