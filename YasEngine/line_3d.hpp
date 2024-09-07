#ifndef LINE_3D_HPP
#define LINE_3D_HPP
#include "vector_3d.hpp"

// To be precise Line Segment
struct Line3D {
  Point3D point0;
  Point3D point1;
  Vector3D direction_vector_of_line;
};

#endif