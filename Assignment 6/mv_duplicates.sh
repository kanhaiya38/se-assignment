#!/bin/bash

echo "Enter location to move all the duplicate files"
read target_location

files=(*)
len=0
count=${#files[@]}
for (( i=0 ; i < count ;i++ )); do
	for (( j=i+1 ; j < count ; j++ )); do
		if diff -q "${files[i]}" "${files[j]}" >/dev/null; then
			# add to array of duplicates
			duplicates[$len]="${files[j]}"
			len=$(( len+1 ))
		fi
	done
done > /dev/null 2>&1

echo "Moving duplicate files"
if [[ ! -d $target_location ]]; then
	mkdir $target_location
fi
mv ${duplicates[@]} $target_location > /dev/null 2>&1
