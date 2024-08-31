#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

template <typename Type>
class Vector3D {
 public:
  Type x_;
  Type y_;
  Type z_;

  Vector3D() {
    this->x_ = 0;
    this->y_ = 0;
    this->z_ = 0;
  }

  Vector3D(Type x, Type y, Type z) {
    this->x_ = x;
    this->y_ = y;
    this->z_ = z;
  }
};

#endif
