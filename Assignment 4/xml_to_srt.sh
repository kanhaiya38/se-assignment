#!/bin/bash

if [[ $# -ne 1 ]]; then
	exit 1
fi

python3 xml_to_srt.py $1
