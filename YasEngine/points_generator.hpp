#ifndef POINTSGENERATOR_HPP
#define POINTSGENERATOR_HPP
#include "Points_2d_Set.hpp"

class PointsGenerator {
 public:
  int points_number_ = 0;
  virtual Points_2d_Set* GeneratePoints(int number_of_numbers,
                                    std::map<int, float>* numbers) = 0;
  virtual Points_2d_Set* GenerateFloatPoints(
      int number_of_numbers,
                                         std::map<float, float>* numbers) = 0;
};

#endif
