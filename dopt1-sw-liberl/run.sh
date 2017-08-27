#!/bin/bash
TIMER="time -f %e"
TESTS=2
for run in `seq ${TESTS}`;
do
    $TIMER ./sw+ tests/$run/base1 tests/$run/base2 > result
    diff result tests/$run/output
done

