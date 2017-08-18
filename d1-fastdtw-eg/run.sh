#!/bin/bash
TIMER="time -f %e"
TESTS=2
for run in `seq ${TESTS}`;
do
    $TIMER ./fastdtw 1000 2 > output
    head -n 1 output > result
    diff result expected_results/1000_2
done

