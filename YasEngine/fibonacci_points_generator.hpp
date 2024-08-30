#ifndef FIBONACCIPOINTSGENERATOR_HPP
#define FIBONACCIPOINTSGENERATOR_HPP
#include <map>

#include "points_generator.hpp"
#include "Points_2d_Set.hpp"

class FibonacciPointsGenerator : public PointsGenerator {
 public:
  ~FibonacciPointsGenerator();
  Points_2d_Set* GeneratePoints(int number_of_numbers,
                            std::map<int, float>* numbers) override;
  Points_2d_Set* GenerateFloatPoints(int number_of_numbers,
                                 std::map<float, float>* numbers) override;
};

#endif