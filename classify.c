/*
 * This program classifies data from a csv file using k means
 */

#include "points.h"
#include "kmeans.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  // check argument validity
  if (argc != 4) {
    printf("Usage: classify path/to/data.csv <k> <d> \n where <k> is the "
           "number of "
           "clusters and <d> the dimensions\n");
    return 1;
  }

  int k = atoi(argv[2]), d = atoi(argv[3]);

  FILE *source_file = fopen(argv[1], "r");
  if (source_file == NULL) {
    printf("%s: not a valid file\n", argv[1]);
  }

  // parse csv file into a (dynamic) array of points
  int points_capacity = 256,
      n = 0; // n is the number of actually recorded points
  Point *points = (Point *)malloc(points_capacity * sizeof(*points));

  char line_buff_in[1024]; // line buffer for input

  for (int i = 0; fgets(line_buff_in, sizeof(line_buff_in), source_file);
       i++, n++) {
    if (i >= points_capacity) {
      // if capacity exceeded
      points_capacity += 256;
      points = (Point *)realloc(points, points_capacity * sizeof(*points));
    }

    points[i] = new_point(d);
    // loop over lines of the csv file

    // parse line into coordinates
    char *token;
    double line_coordinates[d]; // d-sized array: coordinates to record from
                                // this line

    token = strtok(line_buff_in, ",");

    if (token == NULL) {
      printf("ATTENTION :Empty item at line %d:", i + 1);
    }

    for (int k = 0; token && k < d; k++) {
      line_coordinates[k] = (double)atof(token);
      token = strtok(NULL, ",");
    }

    apply_coords(&points[i], line_coordinates);
  }

  for (int i = 0; i < n; i++) {
    print_point(points[i]);
    // printf("point of dimension %d\n", d);
  }

  printf("Number of recorded points: %d\n", n);

  // apply kmeans algorithms to k, n, d, points with random initial points
  Point *centroids = generate_random_points(k, d, 42);

  // call the classification algorithm
  int *classes = kmeans(k, n, d, centroids, points);

  // write output file
  char output_filename[256];
  char *input_filename = strtok(argv[1], "."); // retrieve name without .csv
  sprintf(output_filename, "%s_%d_means.csv", input_filename, k);

  FILE *dest_file = fopen(output_filename, "w");
  char line_buff_out[1024]; // line buffer for output

  rewind(source_file);
  for (int i = 0; fgets(line_buff_in, sizeof(line_buff_in), source_file); i++) {
    line_buff_in[strcspn(line_buff_in, "\n")] = '\0'; // strip the newline char

    fprintf(dest_file, "%s, %d\n", line_buff_in,
            classes[i]); // save class to each line
  }

  fclose(dest_file);
  fclose(source_file);

  free(points);
  free(centroids);
  return 0;
}
