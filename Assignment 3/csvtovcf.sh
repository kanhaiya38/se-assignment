#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Incorrect usage"
	echo "usage: ./csvtovcf.sh <file_name>.csv"
	exit 1
fi

if [[ $1 != *.csv ]]; then
	echo "Please give proper csv file as input"
	exit 1
fi

# file
ip_file=$1
op_file=${1%.csv}.vcf

# get first line with all headings
read line <$ip_file
for i in $line; do
	headers+=($i)
done

# if file already exists remove it
if [[ -f $op_file ]]; then
	rm $op_file
fi

# get all lines except first one
tail -n +2 $ip_file >$ip_file.tmp

while read line; do
	# set IFS to seperate on comma
	PREV_IFS=$IFS
	IFS=,
	# array initialization
	values=()
	for i in $line; do
		values+=($i)
	done

	# write vcf
	echo "BEGIN:VCARD" >>$op_file
	echo "VERSION:2.1" >>$op_file
	echo "N:${values[0]};${values[1]}" >>$op_file
	echo "FN:${values[0]}" >>$op_file
	echo "EMAIL:${values[2]}" >>$op_file
	echo "TEL:${values[3]}" >>$op_file
	echo "END:VCARD" >>$op_file

	# clear array
	unset values

	# unset ifs
	IFS=$PREV_IFS
done <$ip_file.tmp

# remove temporary file
rm $ip_file.tmp
