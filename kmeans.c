#include "kmeans.h"
#include "points.h"

// #include <stdio.h>
#include <stdlib.h>

int closest(Point point, Point *others, int k) {
  int min_id = 0;
  double min_dist = l2_dist_sq(point, others[min_id]);

  for (int j = 1; j < k; j++) {
    double current_dist = l2_dist_sq(point, others[j]);
    if (current_dist <= min_dist) {
      min_id = j;
      min_dist = current_dist;
    }
  }

  return min_id;
}

int *kmeans(int k, int n, int d, Point *centroids, Point *points) {
  int *res = calloc(n, sizeof *res);

  int stop = 0;
  int max_iter = 100000;
  int iter;

  for (iter = 0; (stop == 0) && (iter < max_iter); iter++) {
    // assign all n points to a centroid (cluster)
    for (int i = 0; i < n; i++) {
      // look for closest centroid
      int min_id = closest(points[i], centroids, k);

      // assign an argmin class
      res[i] = min_id;
    }

    // update centroids
    stop = 1; // this will be changed to 0 before end of iteration
    // if stopping condition not met
    for (int j = 0; j < k; j++) {
      // average points of class j
      Point new_center_j = find_centroid_j(k, n, j, d, points, res);
      stop = stop && equals(new_center_j, centroids[j]);
      centroids[j] = new_center_j;
    }
  }

  printf("Number of iterations: %d\n", iter);
  return res;
}

Point find_centroid_j(int k, int n, int j, int d, Point *points, int *classes) {
  Point centroid = new_point(d); // init with zeros
  int count = 0;

  // sum over points of class j
  for (int i = 0; i < n; i++) {
    if (classes[i] == j) {
      centroid = add(centroid, points[i]);
      count++;
    }
  }

  return scale_point(centroid, 1.0 / ((double)count));
}
