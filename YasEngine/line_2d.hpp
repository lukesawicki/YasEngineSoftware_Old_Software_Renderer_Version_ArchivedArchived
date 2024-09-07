#ifndef LINE_2D_HPP
#define LINE_2D_HPP
#include "vector_2d.hpp"

// To be precise Line Segment
struct Line2D {
  Point2D point0;
  Point2D point1;
  Vector2D direction_vector_of_line;
};

#endif