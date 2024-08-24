#ifndef POINTSGENERATOR_HPP
#define POINTSGENERATOR_HPP
#include "points_set.hpp"

class PointsGenerator {
 public:
  int points_number_ = 0;
  virtual PointsSet* GeneratePoints(int number_of_numbers,
                                    std::map<int, float>* numbers) = 0;
  virtual PointsSet* GenerateFloatPoints(int number_of_numbers,
                                         std::map<float, float>* numbers) = 0;
};

#endif
