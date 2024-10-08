#ifndef MATH_PICTURE_HPP
#define MATH_PICTURE_HPP
#include <map>

#include "points_generator.hpp"

class MathPicture {
 public:
  MathPicture(std::map<int, float>* numbers, PointsGenerator* points_Generator);
  MathPicture(std::map<float, float>* float_numbers,
              PointsGenerator* points_generator);
  ~MathPicture();
  void GeneratePoints();

  int base_points_fuel_ = 0;
  int minimal_points_fuel_ = 0;
  PointsGenerator* points_generator_;
  PointsSet* points_set_;
  std::map<int, float>* numbers_;
  std::map<float, float>* float_numbers_;
};

#endif
