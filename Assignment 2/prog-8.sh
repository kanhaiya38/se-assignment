#!/bin/bash

# 8. to display the result a student has scored (same as 5th program) using case...esac statement. 

echo "Enter your marks"
read marks

case $marks in
	9[1-9]|100) echo "I - Division";;
	8[1-9]|90) echo "II - Division";;
	7[1-9]|80) echo "III - Division";;
	*) echo "Fail";;
esac
