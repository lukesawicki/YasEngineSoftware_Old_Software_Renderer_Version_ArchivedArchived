#ifndef COSINUSPOINTSGENERATOR_HPP
#define COSINUSPOINTSGENERATOR_HPP
#include <map>

#include "points_generator.hpp"

class CosinePointsGenerator : public PointsGenerator {
 public:
  ~CosinePointsGenerator();
  Points_2d_Set* GeneratePoints(int number_of_numbers,
                            std::map<int, float>* numbers) override;
  Points_2d_Set* GenerateFloatPoints(int number_of_numbers,
                                 std::map<float, float>* numbers) override;
};

#endif
