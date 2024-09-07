#ifndef VECTOR_4D_HPP
#define VECTOR_4D_HPP

typedef class Vector4D {
 public:
  float x_;
  float y_;
  float z_;
  float w_;

  Vector4D() {
    this->x_ = 0;
    this->y_ = 0;
    this->z_ = 0;
    this->w_ = 0;
  }

  Vector4D(float x, float y, float z, float w = 0) {
    this->x_ = x;
    this->y_ = y;
    this->z_ = z;
    this->w_ = w;
  }

  Vector4D(const Vector4D* vector_4d) {
    x_ = vector_4d->x_;
    y_ = vector_4d->y_;
    z_ = vector_4d->z_;
    w_ = vector_4d->w_;
  }
};

#endif
