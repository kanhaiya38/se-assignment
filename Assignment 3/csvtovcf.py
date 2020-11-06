import sys
import csv

file_name = sys.argv[1]

with open(file_name) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    headers = []
    for row in csv_reader:
        if line_count == 0:
            headers = row
            line_count += 1
        else:
            print("BEGIN:VCARD")
            print("VERSION:2.1")
            print("N:{};{}".format(row[0], row[1]))
            print("FN:{}".format(row[0]))
            print("EMAIL:{}".format(row[2]))
            print("TEL:{}".format(row[3]))
            print("END:VCARD")
            line_count += 1
