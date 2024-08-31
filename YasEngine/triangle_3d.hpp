#ifndef TRIANGLE_3D_HPP
#define TRIANGLE_3D_HPP
#include "vector_4d.hpp"

struct Triangle3D {
  Vector4D<float>* first_vertex;
  Vector4D<float>* second_vertex;
  Vector4D<float>* third_vertex;
};

#endif