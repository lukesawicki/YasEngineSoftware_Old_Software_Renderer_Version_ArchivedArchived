#ifndef TRIANGLE_3D_HPP
#define TRIANGLE_3D_HPP
#include "vector_4d.hpp"

struct Triangle3D {
  Vector4D<float>* first_vertex;
  Vector4D<float>* second_vertex;
  Vector4D<float>* third_vertex;

    Triangle3D() {
      
    }


  Triangle3D(const Triangle3D* triangle) {
    first_vertex = new Vector4D<float>(triangle->first_vertex);
    second_vertex = new Vector4D<float>(triangle->second_vertex);
    third_vertex = new Vector4D<float>(triangle->third_vertex);
  }

};

#endif