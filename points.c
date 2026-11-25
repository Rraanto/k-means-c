#include <stdio.h>
#include <stdlib.h>

#include "points.h"

/**
 * Constructor methods
 */
Point new_point(int d) {
  // allocate d memory slots for the float coordinates
  Point p;

  p.d = d;
  // initialise with zeros
  p.coords = calloc(d, sizeof(*p.coords));

  return p;
}

void apply_coords(Point *p, double *coords) {
  for (int i = 0; i < p->d; i++) {
    p->coords[i] = coords[i];
  }
}

Point *generate_random_points(int n, int d, int seed) {
  srand(seed);
  Point *points = (Point *)malloc(n * sizeof(*points));

  for (int i = 0; i < n; i++) {
    points[i] = new_point(d);
    for (int j = 0; j < d; j++)
      points[i].coords[j] = (double)rand() / RAND_MAX;
  }

  return points;
}

/**
 * Algebraic operations
 */
Point add(Point a, Point b) {
  int d = a.d;
  Point p = new_point(d);

  for (int i = 0; i < d; i++)
    p.coords[i] = a.coords[i] + b.coords[i];

  return p;
}

int equals(Point a, Point b) {
  int res = 1;
  for (int i = 0; (i < a.d) && res; i++) {
    res = res && (a.coords[i] == b.coords[i]);
  }

  return res;
}

Point sum(Point *points, size_t nb_points) {
  int d = points[0].d;
  Point p = new_point(d);

  // this layout seems to be more prone to parallelism later
  for (int i = 0; i < d; i++) {
    for (int j = 0; j < nb_points; j++)
      p.coords[i] += points[j].coords[i];
  }

  return p;
}

Point scale_point(Point point, double lambda) {
  int d = point.d;
  Point p = new_point(d);
  for (int i = 0; i < d; i++)
    p.coords[i] = point.coords[i] * lambda;

  return p;
}

Point mean(Point *points, size_t nb_points) {
  return scale_point(sum(points, nb_points), (double)(1.0 / (double)nb_points));
}

/**
 * Geometry
 */
double l2_dist_sq(Point a, Point b) {
  double res = 0.0;
  for (int i = 0; i < a.d; i++)
    res += (a.coords[i] - b.coords[i]) * (a.coords[i] - b.coords[i]);

  return res;
}

/**
 * IO and testing
 */
void print_point(Point p) {
  printf("(");
  for (int i = 0; i < p.d; i++) {
    printf("%f", p.coords[i]);

    if (i != p.d - 1)
      printf(",");
  }
  printf(")\n");
}
