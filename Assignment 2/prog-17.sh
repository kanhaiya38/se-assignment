#!/bin/bash

# 17. to write the following contents in a file:-
# cat
# dog
# bear
# hello
# elephant
# hello
# tiger
# hello
# horse
# and then delete the lines containing the word "hello"
# and display the file. (Hint: use grep command)

echo "Enter file name"
read file

grep -v "hello" $file > $file.tmp && mv $file.tmp $file

echo
echo "Content of the file $file"
cat $file
