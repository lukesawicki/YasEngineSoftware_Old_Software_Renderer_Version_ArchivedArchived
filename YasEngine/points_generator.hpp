#ifndef POINTSGENERATOR_HPP
#define POINTSGENERATOR_HPP
#include "points_set.hpp"

class PointsGenerator {
 public:
  int points_number_ = 0;
  virtual PointsSet* generatePoints(int numberOfNumbers,
                                    std::map<int, float>* numbers) = 0;
  virtual PointsSet* generateFloatPoints(int numberOfNumbers,
                                         std::map<float, float>* numbers) = 0;
};

#endif
