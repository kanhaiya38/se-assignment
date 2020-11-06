#!/bin/bash

# 12. to check and display 10 leap years from year 2000.

check_leap_year() {
	if (( $1 % 100 == 0 )); then
		if (( $1 % 400 != 0 )); then
			return 1;
		fi
	else
		if (( $1 % 4 != 0 )); then
			return 1;
		fi
	fi
}

year=2000
i=0

while (( $i < 10 )); do
	if check_leap_year $year; then
		echo "$year";
		(( i += 1 ))
	fi
	(( year += 1 ))
done
