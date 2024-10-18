#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <iostream>
#include <vector>
typedef struct {
  double x, y, z;
} coords;
std::vector<coords> fileLoaderVerts(std::string filename, long *verts);
std::vector<double> fileLoaderFaces(std::string filename, long *edges);
double ratioDef(std::vector<coords> vect, std::vector<double> arr, long verts,
                long edges);
#endif  // TRANSFORM_H
