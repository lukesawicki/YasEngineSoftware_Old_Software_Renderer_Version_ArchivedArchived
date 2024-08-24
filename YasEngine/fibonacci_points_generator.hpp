#ifndef FIBONACCIPOINTSGENERATOR_HPP
#define FIBONACCIPOINTSGENERATOR_HPP
#include <map>

#include "points_generator.hpp"
#include "points_set.hpp"

class FibonacciPointsGenerator : public PointsGenerator {
 public:
  ~FibonacciPointsGenerator();
  PointsSet* generatePoints(int numberOfNumbers,
                            std::map<int, float>* numbers) override;
  PointsSet* generateFloatPoints(int numberOfNumbers,
                                 std::map<float, float>* numbers) override;
};

#endif