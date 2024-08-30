#ifndef SINUSPOINTSGENERATOR_HPP
#define SINUSPOINTSGENERATOR_HPP
#include <map>

#include "points_generator.hpp"
#include "points_2d_set.hpp"

class SinePointsGenerator : public PointsGenerator {
 public:
  ~SinePointsGenerator();
  Points_2d_Set* GeneratePoints(int number_of_numbers,
                            std::map<int, float>* numbers) override;
  Points_2d_Set* GenerateFloatPoints(int number_of_numbers,
                                 std::map<float, float>* numbers) override;
};

#endif