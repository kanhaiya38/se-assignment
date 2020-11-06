#!/bin/bash

# 15. to check two file contents are same.
# ( Hint: use cmp or diff  command ).

echo "Enter name of first file"
read file1;
echo "Enter name of second file"
read file2;

echo

if cmp $file1 $file2; then
	echo "Content of both files is the same"
else
	echo "Content of both files is different"
fi

