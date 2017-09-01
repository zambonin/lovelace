#!/bin/bash

EXEC=./gou

for input_file in tests/*
do
    input=${input_file#tests/}
    echo $input
    $EXEC $input > output
    diff output "$input_file"
done
rm output
