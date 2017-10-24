#!/bin/bash
TIMER="time -f %e"
TESTS=2
EXEC=sw
for run in `seq ${TESTS}`;
do
    $TIMER ./$EXEC tests/$run/base1 tests/$run/base2 > result
    diff result tests/$run/output
    rm result
done

