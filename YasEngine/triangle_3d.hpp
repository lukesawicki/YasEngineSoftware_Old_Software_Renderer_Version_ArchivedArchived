#ifndef TRIANGLE_3D_HPP
#define TRIANGLE_3D_HPP
#include "vector_4d.hpp"

struct Triangle3D {
  Vector4D* first_vertex;
  Vector4D* second_vertex;
  Vector4D* third_vertex;

    Triangle3D() {
      
    }


  Triangle3D(const Triangle3D* triangle) {
    first_vertex = new Vector4D(triangle->first_vertex);
    second_vertex = new Vector4D(triangle->second_vertex);
    third_vertex = new Vector4D(triangle->third_vertex);
  }

};

#endif
