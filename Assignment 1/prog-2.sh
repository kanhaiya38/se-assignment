#!/bin/bash

# 2. to check the given integer is prime or not.

check_prime() {
	(($1 != 2 && $1 % 2 == 0)) && return 1

	sqrt=$(bc <<< "sqrt($1)")

	for ((i = 3; i < $sqrt; i += 2)); do
		(( $1 % $i == 0)) && return 1
	done

	return 0
}

echo "Enter a number"
read num

if check_prime $num; then
	echo "It is prime"
else
	echo "It is not a prime number"
fi
