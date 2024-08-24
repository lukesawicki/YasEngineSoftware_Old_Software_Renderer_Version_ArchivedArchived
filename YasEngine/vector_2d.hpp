#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>

template <typename Type>
class Vector2D {
 public:
  Type x_;
  Type y_;

  Vector2D() {
    this->x_ = 0;
    this->y_ = 0;
  }

  Vector2D(Type x, Type y) {
    this->x_ = x;
    this->y_ = y;
  }

  static void normalizedVector(Vector2D<Type>& vector) {
    double magnitude = getVectorMagnitude(vector);
    double x = vector.x_ / magnitude;
    double y = vector.y_ / magnitude;
    vector.x_ = static_cast<Type>(x);
    vector.y_ = static_cast<Type>(y);
  }

  static Type getVectorMagnitude(const Vector2D<Type>& vector) {
    return static_cast<Type>(sqrt(pow(vector.x_, 2.0) + pow(vector.y_, 2.0)));
  }

  static Type getVectorMagnitude(Type x0, Type y0, Type x1, Type y1) {
    return static_cast<Type>(sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0)));
  }

  static Type crossProduct(const Vector2D<Type>& u, const Vector2D& v) {
    return u.x_ * v.y_ - u.y_ * v.x_;
  }

  static Type dotProduct(const Vector2D<Type>& u, const Vector2D& v) {
    return u.x_ * v.x_ + u.y_ * v.y_;
  }

  static Type angleBetweenVectors(const Vector2D<Type>& u, const Vector2D& v) {
    return atan2(crossProduct(u, v), dotProduct(u, v));
  }

  static void rotateVectorOverTheAngle(Vector2D<Type>* v, float angle) {
    float modifiedX = v->x_ * cos(angle) - v->y_ * sin(angle);
    float modifiedY = v->x_ * sin(angle) + v->y_ * cos(angle);

    v->x_ = modifiedX;
    v->y_ = modifiedY;
  }

  static Vector2D<Type> createUnitVectorFromBoundVector(const Vector2D<Type>& u,
                                                        const Vector2D& v) {
    Vector2D<Type> w = Vector2D<Type>(u.x_ - v.x_, u.y_ - v.y_);
    Vector2D::normalizedVector(w);
    return w;
  }

  // minuend => odjemna  - subtrahed => odjemnik
  static void substract(Vector2D<Type>* minued,
                        const Vector2D<Type>& subtrahed) {
    minued->x_ = minued->x_ - subtrahed.x_;
    minued->y_ = minued->y_ - subtrahed.y_;
  }

  static void multiplyByScalar(Vector2D<Type>* v, Type scalar) {
    v->x_ = v->x_ * scalar;
    v->y_ = v->y_ * scalar;
  }
};

#endif
