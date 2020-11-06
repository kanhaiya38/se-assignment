#!/bin/bash

# 13. to check the given string is palindrome or not.

is_palindrome() {
	str=$1
	len=${#str}

	for (( i = 0; i < len / 2; i++)); do
		if [[ ${str:i:1} != ${str:len-i-1:1} ]]; then
			return 1
		fi
	done
}

echo "Enter the string"
read str

if is_palindrome $str; then
	echo "String is a palindrome"
else
	echo "String is not a palindrome"
fi
