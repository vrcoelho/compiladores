#!/bin/bash

expected_lines=$(wc -l expected | tr -d '\n\r expected')

./etapa1 test_file > out

# compare only the first $expected_lines lines of the lines
# so ignoring the hash table printed at the end of main
diff_output=$(diff <(head -n $expected_lines out) <(head -n $expected_lines expected))

if [ -z "$diff_output" ]
then
    # var is empty
    # no errors
    echo "TESTS PASSED"
    exit 0
else
    # var is not empty
    # diff returned an error
    echo $diff_output
    exit 1
fi
