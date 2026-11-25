/**
 * Implementation of the kmeans algorithm based on the points library
 */

#ifndef KMEANS_H
#define KMEANS_H

#include "points.h"
#include <stdio.h>

/*
 * General k means algorithm
 *
 * inputs:
 * - k: number of classes / clusters (int)
 * - n: number of points to cluster (int)
 * - d: dimension of each point (int)
 * - centroids: list of k centroids to start with (Points*)
 * - points: points to classify (Points*)
 *
 * outputs:
 * - classes (int[n])
 */

int *kmeans(int k, int n, int d, Point *centroids, Point *points);

/**
 * Util functions
 */
int closest(Point point, Point *others, int k);

/*
 * Find centroid of cluster j (amongst population of class j)
 */
Point find_centroid_j(int k, int n, int j, int d, Point *points, int *classes);

#endif
