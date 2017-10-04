#!/usr/bin/env python
# -*- coding: utf-8 -*-

from csv import reader, writer
from math import sqrt
from operator import itemgetter
from sys import argv


def open_csv(path):
    with open(path, 'r') as csvfile:
        data = list(reader(csvfile))
        points = [[i[0]] + [float(k) for k in i[1:]] for i in data[1:]]
        return points, data[0]

def norm(vector1, vector2):
    distance = 0
    for i, j in zip(vector1, vector2):
        distance += pow(i - j, 2)
    return sqrt(distance)


class KNN():
    def __init__(self, path, K):
        self.nclu = K
        self.data, self.header = open_csv(path)

    def write_csv(self, data, path):
        with open(path, 'w') as csvfile:
            _writer = writer(csvfile)
            _writer.writerow(self.header)
            _writer.writerows(data)

    def get_neighbors(self, item):
        distances = [(line, norm(line[1:], item[1:]))
                     for line in self.data]
        distances.sort(key=itemgetter(1))
        return [distances[i][0] for i in range(self.nclu)]

    def classify_line(self, item):
        neighbors = self.get_neighbors(item)
        types = {n[0] : 0 for n in neighbors}
        for neighbor in neighbors:
            types[neighbor[0]] += bool(neighbor[0] in types)
        return sorted(types, key=types.get, reverse=True)[0][0]

    def classify(self, path):
        data, header = open_csv(path)
        assert header == self.header, "Incompatible data sets!"

        prediction = []
        for line in data:
            line[0] = self.classify_line(line)
            prediction.append(line)
        return prediction


if __name__ == '__main__':
    try:
        classifier = KNN(argv[1], int(argv[4]))
        classifier.write_csv(classifier.classify(argv[2]), argv[3])
    except Exception as e:
        print(e)
