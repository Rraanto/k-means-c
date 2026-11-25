# K-means in C 

Coding exercise implementing K means algorithm in C from nothing. In a nutshell, `points` define the `Point` structure that represents vectors in a given $\mathbb R^d$ and useful operations (averaging, summing, scaling ...) and `kmeans` contains the main K-means implementation.  

# Compile and run 
This program has been compiled using `cc` (with optionally naming the output executable `classify`): 

```bash
cc points.c kmeans.c classify.c -o classify
```

And can be used with exactly 3 command line arguments: 
- `path/to/source.csv` : path to the csv containing the data to classify. This data should ideally be normalised to $[0, 1]^d$ (although the algorithm works anyways) and should be formatted in some way (see later in the Readme) 
- `k`: the `k` parameter in `k`-means (number of classes) 
- `d`: the dimension of the data

The following example applies the k means algorithm to a 2D point cloud saved in the file `test_files/2d_point_cloud.csv` with 4 categories
```bash
classify test_files/2d_point_cloud.csv 4 2
```
It outputs a file `test_files/2d_point_cloud_4_means.csv` containing an additional column containing an integer corresponding to the class of each point.

# K means algorithm

The following algorithm classifies a set of points $\{ x_i \}\_{i=1}^N, N \in \mathbb N^*, x_i \in \mathbb R^d \forall 0 \leq i \leq N, d \in \mathbb N^*$ into $K \in \mathbb N^*$ classes such that each class define a neighborhood (based on some distance).

First, some set of points $\{ \mu_1^{[0]}, \dots, \mu_K^{[0]} \}$ are initialised at step $0$, they will play the role of "centroids" or "cluster centers".

Then each $x_i, 0 \leq i \leq N$ is given a class $c(x_i)$ based on which centroid is nearest. Then, each cluster $C_k$ comprised of those $x_i$'s that have been assigned the class $c(x_i) = k$ will have a new centroid, defined by their geometric center. This define the iterative scheme defined by:

For $j \geq 1$

**assignment step**
$$c^{[j]}(x_i) \in \text{arg}\min\limits_{k \in \{0, \dots, K\}} d(x_i, \mu_k^{[j]})$$

**update step**
For each $k \in {1, \dots, K }$
$$\mu_k^{[j]} = \frac{1}{|C_k^{[j]}|} \sum\limits_{1 \leq i \leq N, c^{[j]}(x_i) = k} x_i$$

Where $|C_k^{[j]}|$ is the number of $x_i$'s in class $k$ : $|C_k| := #\{ i \in \{ 1, \dots, N \} | c^{[j]}(x_i) = k \}$

With the stopping criterion at $j+1$ such that $$\mu_k^{[j+1]} = \mu_k^{[j]}, \forall k \in \{1, \dots, K\}$$

# Code architecture 

In a nutshell, the `classify` program output by `classify.c` takes as input a csv file `input.csv`, integers `k (number of classes), d (dimension)`  and outputs a similar `input_<k>_means.csv` with an additional column specifying the class output by the algorithm: 

```
/*********************/ 
/                     /
/     input.csv       /
/                     /
/*********************/ 
           |
      classify.c
           |
/*********************/ 
/                     /
/     Point points[n] /
/                     /
/*********************/ 
           |
       kmeans.c
           |
/*********************/ 
/                     /
/    int classes[n]   /
/                     /
/*********************/ 
           |
       classify.c
           |
/*********************/ 
/                     /
/   input_<k>_means.csv     /
/                     /
/*********************/ 
```

# Behavior of the program 
## Parsing input csv file 
The csv file to parse should contain coordinate lines using comma `","` as separation and no header lines: it should exactly look like this: 
```
1, 2, 5, 1.0
```
Which will be parsed as the `Point` variable :
```C 
{
  int d = 4; 
  double coordinates[] = {1.0, 2.0, 5.0, 1.0}
}
```

## Applying the algorithm
## Writing classes to an output file
