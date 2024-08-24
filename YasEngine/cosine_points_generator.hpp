#ifndef COSINUSPOINTSGENERATOR_HPP
#define COSINUSPOINTSGENERATOR_HPP
#include <map>

#include "points_generator.hpp"

class CosinePointsGenerator : public PointsGenerator {
 public:
  ~CosinePointsGenerator();
  PointsSet* GeneratePoints(int number_of_numbers,
                            std::map<int, float>* numbers) override;
  PointsSet* GenerateFloatPoints(int number_of_numbers,
                                 std::map<float, float>* numbers) override;
};

#endif
