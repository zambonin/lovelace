#!/bin/bash
TIMER="time -f %e"
TESTS=2
for run in `seq ${TESTS}`;
do
    $TIMER ./SmithWaterman.py tests/1/base1 tests/1/base2 > result
    diff result tests/1/output
done

