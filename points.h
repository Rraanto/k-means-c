/**
 * Utilitary library that defines d-dimensional points and their algebraic
 * operations
 */

#ifndef POINTS_H
#define POINTS_H

#include <stdio.h>

typedef struct Point {
  int d;          // dimension
  double *coords; // coordinates
} Point;

/*
 * Constructor methods
 */
Point new_point(int d);

void apply_coords(Point *p, double *coords);
// Point new_point(int d, double *coords);

/*
 * Algebraic operation between poinst
 */
Point add(Point a, Point b);
int equals(Point a, Point b);
Point sum(Point *points, size_t nb_points);
Point mean(Point *points, size_t nb_points);

/*
 * Geometric operations (distances, norms)
 */
double l2_norm_sq(Point p);
double l2_dist_sq(Point a, Point b);

/*
 * Higher level "data" manipulation operations
 */

Point scale_point(Point point, double lambda);

Point mean(Point *points, size_t k);

/**
 * Utilitary functions (IO)
 */

void print_point(Point p);
#endif
