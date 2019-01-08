#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""knn.py

A simple module implementation for the k-nearest-neighbors pattern recognition
algorithm."""

from __future__ import absolute_import
from csv import QUOTE_MINIMAL, reader, writer
from operator import itemgetter
from sys import argv


def open_csv(path):
    """Helper function to read a CSV file describing points."""
    with open(path, "r") as csvfile:
        data = list(reader(csvfile))
        points = [[i[0]] + [float(k) for k in i[1:]] for i in data[1:]]
        return points, data[0]


class KNN:
    """Class that acts as a wrapper for instances of sets of points."""

    def __init__(self, path, K):
        self.nclu = K
        self.data, self.header = open_csv(path)

    def write_csv(self, data, path):
        """Helper method to write a CSV containing reorganized points."""
        with open(path, "w") as csvfile:
            _writer = writer(csvfile, dialect="unix", quoting=QUOTE_MINIMAL)
            _writer.writerow(self.header)
            _writer.writerows(data)

    def get_neighbors(self, item):
        """Obtain all closest neighbors of a point."""
        distances = []
        for line in self.data:
            distance = 0
            for i, j in zip(line[1:], item[1:]):
                distance += (i - j) ** 2
            distances.append((line, distance))
        distances.sort(key=itemgetter(1))
        return [distances[i][0] for i in range(self.nclu)]

    def classify_line(self, item):
        """Apply classification to a point according to its neighbors."""
        neighbors = self.get_neighbors(item)
        types = {n[0]: 0 for n in neighbors}
        for neighbor in neighbors:
            types[neighbor[0]] += bool(neighbor[0] in types)
        return sorted(types, key=types.get, reverse=True)[0][0]

    def classify(self, path):
        """Classify the whole test set according to a data set."""
        data, header = open_csv(path)
        assert header == self.header, "Incompatible data sets!"

        prediction = []
        for line in data:
            line[0] = self.classify_line(line)
            prediction.append(line)
        return prediction


if __name__ == "__main__":
    try:
        CLASSIFIER = KNN(argv[1], int(argv[4]))
        CLASSIFIER.write_csv(CLASSIFIER.classify(argv[2]), argv[3])
    except (IndexError, FileNotFoundError, ValueError):
        raise SystemExit("Invalid arguments!")
