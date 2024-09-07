#ifndef VECTOR_4D_HPP
#define VECTOR_4D_HPP

typedef class Vector3D {
 public:
  float x_;
  float y_;
  float z_;

  Vector3D() {
    this->x_ = 0;
    this->y_ = 0;
    this->z_ = 0;
  }

  Vector3D(float x, float y, float z, float w = 0) {
    this->x_ = x;
    this->y_ = y;
    this->z_ = z;
  }

  Vector3D(const Vector3D* vector_4d) {
    x_ = vector_4d->x_;
    y_ = vector_4d->y_;
    z_ = vector_4d->z_;
  }
} Point3D;

#endif
