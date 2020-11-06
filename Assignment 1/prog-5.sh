#!/bin/bash

# 5. to take subject marks as input from user and display the result
# (I-division, II-division, III-division, fail)

echo "Enter your marks"
read marks

if [[ $marks -ge 90 ]]; then
	echo "I - Division"
elif [[ $marks -ge 80 ]]; then
	echo "II - Division"
elif [[ $marks -ge 70 ]]; then
	echo "III - Division"
else
	echo "Fail"
fi
