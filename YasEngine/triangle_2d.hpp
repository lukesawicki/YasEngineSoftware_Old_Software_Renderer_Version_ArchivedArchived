#ifndef TRIANGLE_2D_HPP
#define TRIANGLE_2D_HPP
#include "vector_2d.hpp"

struct Triangle2D {
  Vector2D* first_vertex;
  Vector2D* second_vertex;
  Vector2D* third_vertex;

  Triangle2D() {
    first_vertex = new Vector2D;
    second_vertex = new Vector2D;
    third_vertex = new Vector2D;
  }
};

#endif
