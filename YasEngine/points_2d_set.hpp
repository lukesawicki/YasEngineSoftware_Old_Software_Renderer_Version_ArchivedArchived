#ifndef POINTSSET_HPP
#define POINTSSET_HPP
#include "vector_2d.hpp"

class Points_2d_Set {
 public:
  Points_2d_Set() {
    points_ = nullptr;
    points_number_ = 0;
  }
  ~Points_2d_Set() {
    delete[] points_;
    points_number_ = 0;
  }
  Points_2d_Set(Vector2D<float>* points, long points_number) {
    points_ = points;
    this->points_number_ = points_number;
  }
  Vector2D<float>* points_ = nullptr;
  long points_number_;
};

#endif
