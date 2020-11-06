#!/bin/bash
# 11. to read the contents of a file 
# and display it line by line in command prompt.
# (Hint: use read command to read the file contents.)

PREV_IFS=$IFS

echo "Enter file name"
read file
echo

file_content=$(cat $file)
IFS=\.

for text in $file_content; do
	echo $text
done

IFS=$PREV_IFS
