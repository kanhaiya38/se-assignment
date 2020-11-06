#!/bin/bash

# 9. to check if a file exists.
# if yes then write "hello world" in the file.
# if no then create the file and then write "hello world" line.

echo "Enter file name"
read file

if [[ -f $file ]]; then
	echo "File exists"
else
	echo "Creating file"
fi
echo "Writing into file..."
echo "hello world" > $file;
