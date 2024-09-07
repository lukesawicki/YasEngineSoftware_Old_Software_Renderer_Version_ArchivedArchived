#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP
#include <cmath>

// x, y -> vector components
// wedlug ilustrowanego slownika matematycznego skladowa = component

typedef class Vector2D {
 public:
  float x_;
  float y_;

  Vector2D() {
    this->x_ = 0;
    this->y_ = 0;
  }

  Vector2D(float x, float y) {
    this->x_ = x;
    this->y_ = y;
  }

    Vector2D(const Vector2D* vector_2d) {
    x_ = vector_2d->x_;
    y_ = vector_2d->y_;
  }

  static void NormalizedVector(Vector2D& vector) {
    double magnitude = GetVectorMagnitude(vector);
    double x = vector.x_ / magnitude;
    double y = vector.y_ / magnitude;
    vector.x_ = static_cast<float>(x);
    vector.y_ = static_cast<float>(y);
  }

  static float GetVectorMagnitude(const Vector2D& vector) {
    return static_cast<float>(sqrt(pow(vector.x_, 2.0) + pow(vector.y_, 2.0)));
  }

  static float GetVectorMagnitude(float x0, float y0, float x1, float y1) {
    return static_cast<float>(sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0)));
  }

  static float CrossProduct(const Vector2D& vector_0, const Vector2D& vector_1) {
    return vector_0.x_ * vector_1.y_ - vector_0.y_ * vector_1.x_;
  }

  static float DotProduct(const Vector2D& vector_0, const Vector2D& vector_1) {
    return vector_0.x_ * vector_1.x_ + vector_0.y_ * vector_1.y_;
  }

  static float AngleBetweenVectors(const Vector2D& vector_0, const Vector2D& vector_1) {
    return atan2(CrossProduct(vector_0, vector_1), DotProduct(vector_0, vector_1));
  }

  static void RotateVectorOverTheAngle(Vector2D* vector, float angle) {
    float modifiedX = vector->x_ * cos(angle) - vector->y_ * sin(angle);
    float modifiedY = vector->x_ * sin(angle) + vector->y_ * cos(angle);

    vector->x_ = modifiedX;
    vector->y_ = modifiedY;
  }

  static Vector2D CreateUnitVectorFromBoundVector(const Vector2D& vector_0,
                                                        const Vector2D& vector_1) {
    Vector2D w = Vector2D(vector_0.x_ - vector_1.x_, vector_0.y_ - vector_1.y_);
    Vector2D::NormalizedVector(w);
    return w;
  }

  static void Substract(Vector2D* vector_0, const Vector2D* vector_1) {
    vector_0->x_ = vector_0->x_ - vector_1->x_;
    vector_0->y_ = vector_0->y_ - vector_1->y_;
  }

    static Vector2D* Substract(const Vector2D* vector_0, const Vector2D* vector_1) {
      Vector2D* resultat = new Vector2D;
      resultat->x_ = vector_0->x_ - vector_1->x_;
      resultat->y_ = vector_0->y_ - vector_1->y_;
    }

    static void Add(Vector2D* vector_0, const Vector2D* vector_1) {
      vector_0->x_ = vector_0->x_ - vector_1->x_;
      vector_0->y_ = vector_0->y_ - vector_1->y_;
    }

    static Vector2D* Add(const Vector2D* vector_0, const Vector2D* vector_1) {
      Vector2D* resultat = new Vector2D;
      resultat->x_ = vector_0->x_ + vector_1->x_;
      resultat->y_ = vector_0->y_ + vector_1->y_;
    }

  static void MultiplyByScalar(Vector2D* vector, float scalar) {
    vector->x_ = vector->x_ * scalar;
    vector->y_ = vector->y_ * scalar;
  }

  static double DistanceBetweenPoints(const Vector2D& vector_0,
                               const Vector2D& vector_1) {
    return sqrt(pow((vector_0.x_ - vector_1.x_), 2) +
                pow((vector_0.y_ - vector_1.y_), 2));
  }

} Point2D;

#endif
