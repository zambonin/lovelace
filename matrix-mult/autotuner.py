#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""autotuner.py

An automated performance tuner selects a distinguished program among a set
of candidates using criteria such as performance or executable size. This
code tests several combinations of compiler flags and software to achieve an
optimal set such that the accompanying matrix multiplication (with handmade
loop tiling) code runs in less time.
"""

from itertools import product, combinations, chain
from subprocess import run, TimeoutExpired
from sys import argv
from time import time

def _run(flags, _time, iterations=20):
    """
    Compiles and runs a certain command, measuring the average time of its
    executions.

    Args:
        flags:      a tuple containing the CC and CFLAGS `make` variables.
        _time:      execution time used to terminate the process if it is
                    too slow; these runs are not needed and can be skipped.
        iterations: number of times a program will be run.

    Returns:
        Average time of executions or the former execution time if the
        process was terminated through a timeout signal.
    """
    run(['make', '-Bs'] + list(flags))
    try:
        run(COMMAND, timeout=_time)
    except TimeoutExpired:
        return _time

    _sum = 0
    for _ in range(iterations):
        start = time()
        run(COMMAND)
        _sum += (time() - start)
    return _sum / iterations


def combine(iterable):
    """
    Organizes elements such that they are chosen without overlap.

    Args:
        iterable:   a list of disjoint sets.

    Returns:
        All possible combinations considering at most one element of each set.
    """
    card = range(len(iterable) + 1)
    pset = chain.from_iterable(combinations(iterable, r) for r in card)
    return list(chain.from_iterable(
        [' '.join(s) for s in product(*i)] for i in pset))


def main():
    """Produces some Makefile combinations and tests a program with them."""
    compilers = ['CC={}'.format(i) for i in ['gcc', 'clang']]
    flag_groups = combine([
        ['-O{}'.format(i) for i in '1 2 3 g s fast'.split()],
        ['-g'],
        ['-march=native'],
    ])
    macro = ['CFLAGS=-DSTEP={}'.format(1 << i) for i in range(6)]

    tuples = list(product(compilers, macro, flag_groups))
    poss = [tuple([i[0], " ".join(i[1:])]) for i in tuples]

    min_time = float('inf')
    cmd = ''

    for i in poss:
        cmd_time = _run(i, min_time)
        if cmd_time < min_time:
            min_time = cmd_time
            cmd = i

    print(cmd, min_time)

if __name__ == '__main__':
    assert len(argv) == 2, "Usage: python {} \"cmd\"".format(argv[0])
    COMMAND = argv[1].split()
    main()
