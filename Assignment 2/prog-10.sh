#!/bin/bash

# 10. make a directory after checking of its existence.

echo "Enter directory name"
read dir

if [[ -d $dir ]]; then
	echo "Directory already exists"
else
	mkdir $dir
	echo "Directory successfully created"
fi
