#!/bin/bash
TIMER="time -f %e"
TESTS=10
for run in `seq ${TESTS}`;
do
    $TIMER ./SmithWaterman.py "$@"
done

