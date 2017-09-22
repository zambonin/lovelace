#!/usr/bin/env python
# -*- coding: utf-8 -*-

from random import gauss, sample, uniform

import numpy as np
import matplotlib.pyplot as plt


class KMeans():
    def __init__(self, K, N):
        self.nclu = K
        self.npts = N
        self.pts = self.gauss_clusters()
        self.centroids = None
        self.clusters = None

    def gauss_clusters(self):
        qty = (self.npts // self.nclu) + 1
        points = []
        for _ in range(self.nclu):
            p_x, p_y = uniform(-1, 1), uniform(-1, 1)
            sigma = uniform(0.05, 0.15)
            points += [np.array([gauss(p_x, sigma), gauss(p_y, sigma)])
                       for _ in range(qty)]
        return points

    def cluster_points(self):
        clusters = {}
        for pnt in self.pts:
            key = np.argmin([np.linalg.norm(pnt - i) for i in self.centroids])
            try:
                clusters[key].append(pnt)
            except KeyError:
                clusters[key] = [pnt]
        self.clusters = clusters

    def find_centers(self):
        old_centroids = sample(self.pts, self.nclu)
        self.centroids = sample(self.pts, self.nclu)

        while not all(np.unique(self.centroids) == np.unique(old_centroids)):
            old_centroids = self.centroids
            self.cluster_points()
            self.centroids = [np.mean(self.clusters[k], axis=0)
                              for k in sorted(self.clusters.keys())]

    def plot_board(self):
        try:
            for cind, cpts in self.clusters.items():
                col = plt.cm.spectral(cind / self.nclu)
                plt.plot(*zip(*cpts), '.', alpha=0.2, color=col)
                plt.plot(*self.centroids[cind], '*', markersize=10)
        except AttributeError:
            plt.plot(*zip(*self.pts), '.', alpha=0.2)
        plt.title("{}-means with random initialization, n = {}".format(
            self.nclu, self.npts))
        plt.tight_layout()
        plt.show()

KMeans(10, 2000).find_centers()
