#ifndef POINT_3D_HPP
#define POINT_3D_HPP
#include <SDL.h>
#include"vector_4d.hpp"

template <typename Type>
class Point3d {
 public:
  Type x_;
  Type y_;
  Type z_;
  Type w_;

  Type r_;
  Type g_;
  Type b_;
  Type a_;

  Point3d() {
    this->x_ = 0;
    this->y_ = 0;
    this->z_ = 0;
    this->w_ = 0;
  }

  Point3d(Type x, Type y, Type z, Type w) {
    this->x_ = x;
    this->y_ = y;
    this->z_ = z;
    this->w_ = w;
  }

  void SetColor(const Vector4D<Uint8>& color) {
    this->r_ = color.x_;
    this->g_ = color.y_;
    this->b_ = color.z_;
    this->a_ = color.w_;
  }

  Point3d(Vector4D<Type> position) {
    this->x_ = position.x_;
    this->y_ = position.y_;
    this->z_ = position.z_;
    this->w_ = position.w_;
  }

};

#endif