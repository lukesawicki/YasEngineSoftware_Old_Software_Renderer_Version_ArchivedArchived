#ifndef TRIANGLE_2D_HPP
#define TRIANGLE_2D_HPP
#include "vector_2d.hpp"

struct Triangle2D {
  Vector2D<float>* first_vertex;
  Vector2D<float>* second_vertex;
  Vector2D<float>* third_vertex;
};

#endif