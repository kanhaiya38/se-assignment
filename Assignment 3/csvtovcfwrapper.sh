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

python3 csvtovcf.py $1 >${1%.csv}.vcf
