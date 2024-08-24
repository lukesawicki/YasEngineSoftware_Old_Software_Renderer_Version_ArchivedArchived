#ifndef FIBONACCIPOINTSGENERATOR_HPP
#define FIBONACCIPOINTSGENERATOR_HPP
#include <map>

#include "points_generator.hpp"
#include "points_set.hpp"

class FibonacciPointsGenerator : public PointsGenerator {
 public:
  ~FibonacciPointsGenerator();
  PointsSet* GeneratePoints(int number_of_numbers,
                            std::map<int, float>* numbers) override;
  PointsSet* GenerateFloatPoints(int number_of_numbers,
                                 std::map<float, float>* numbers) override;
};

#endif