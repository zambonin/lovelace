#!/usr/bin/env python
# -*- coding: utf-8 -*-
# pylint: disable=C0103

"""fw.py

Simple Python implementation of the Floyd-Warshall graph algorithm."""

from __future__ import absolute_import
from sys import argv


def floyd_warshall(m):
    """Uses the adjacency matrix `m` to find shortest pairs between all
    pairs of vertices."""
    n = len(m)
    for i in range(n):
        for f in range(n):
            for d in range(n):
                _sum = m[f][i] + m[i][d]
                if _sum < m[f][d]:
                    m[f][d] = _sum
    return m


def fw_print(m):
    """Pretty-prints the adjacency matrix `m`."""
    print("All pair shortest distances")
    for i in m:
        for j in i:
            print("{:7}".format(j), end="")
        print()


def main():
    """Reads the input file and executes the algorithm."""
    assert len(argv) == 2
    with open(argv[1], "r") as f:
        data = f.readlines()
        n = int(data[0].split(" ")[0])
        m = [[float("inf") for i in range(n)] for j in range(n)]
        for i in range(n):
            m[i][i] = 0
        for i in data[1:]:
            raw = list(map(int, i.split(" ")))
            m[raw[0]][raw[1]] = min(raw[2], m[raw[0]][raw[1]])
        fw_print(floyd_warshall(m))


if __name__ == "__main__":
    main()
