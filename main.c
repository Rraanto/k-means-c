#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "points.h"
#include "kmeans.h"

/*
 * Generates a random vector of size d
 */
double *random_vector(int d);

int main() {
  srand((unsigned)time(NULL));
  // srand(42);
  int d = 5, n = 9, k = 2;
  Point p1 = new_point(d);
  Point p2 = new_point(d);
  Point p3 = new_point(d);
  Point p4 = new_point(d);
  Point p5 = new_point(d);
  Point p6 = new_point(d);
  Point p7 = new_point(d);
  Point p8 = new_point(d);
  Point p9 = new_point(d);

  // 3-means algorithm
  Point centroids[] = {p1, p4};
  Point points[] = {p1, p2, p3, p4, p5, p6, p7, p8, p9};
  for (int i = 0; i < n; i++) {
    apply_coords(&points[i], random_vector(d));
  }

  int *classes = kmeans(k, n, d, centroids, points);

  for (int i = 0; i < n; i++) {
    print_point(points[i]);
    printf("Class of point %d: %d\n", i + 1, classes[i]);
  }
}

double *random_vector(int d) {
  double *x = malloc(d * sizeof *x);

  for (int i = 0; i < d; i++) {
    x[i] = (double)rand() / RAND_MAX;
  }

  return x;
}
