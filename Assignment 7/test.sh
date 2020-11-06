#!/bin/bash

# Test 0
diff <(python3 code.py 0) <(echo "")
if [ $? -ne 0 ]; then
    echo "Test Case 0 Failed"
fi

# Test 1
diff <(python3 code.py 1) <(echo "")
if [ $? -ne 0 ]; then
    echo "Test Case 1 Failed"
fi

# Test 2
diff <(python3 code.py 2) <(echo "2 ")
if [ $? -ne 0 ]; then
    echo "Test Case 2 Failed"
fi

# Test 3
diff <(python3 code.py 50) <(echo "2 3 5 7 11 13 17 19 23 29 31 37 41 43 49 ")
if [ $? -ne 0 ]; then
    echo "Test Case 3 Failed"
fi

# Test 4
diff <(python3 code.py 100) <(echo "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 ")
if [ $? -ne 0 ]; then
    echo "Test Case 4 Failed"
fi
