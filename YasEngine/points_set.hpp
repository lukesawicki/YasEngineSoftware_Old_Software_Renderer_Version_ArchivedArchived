#ifndef POINTSSET_HPP
#define POINTSSET_HPP
#include "vector_2d.hpp"

class PointsSet {
 public:
  PointsSet() {
    points_ = nullptr;
    points_number_ = 0;
  }
  ~PointsSet() {
    delete[] points_;
    points_number_ = 0;
  }
  PointsSet(Vector2D<float>* newPoints, long pointsNumber) {
    points_ = newPoints;
    this->points_number_ = pointsNumber;
  }
  Vector2D<float>* points_ = nullptr;
  long points_number_;
};

#endif
