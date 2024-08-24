#ifndef PRIMENUMBERSPOINTSGENERATOR_HPP
#define PRIMENUMBERSPOINTSGENERATOR_HPP
#include <map>

#include "mathematics.hpp"
#include "points_generator.hpp"
#include "points_set.hpp"

class PrimeNumbersPointsGenerator : public PointsGenerator {
 public:
  static std::vector<int> numbers_;
  ~PrimeNumbersPointsGenerator();
  PointsSet* generatePoints(int numberOfNumbers,
                            std::map<int, float>* numbers) override;
  PointsSet* generateFloatPoints(int numberOfNumbers,
                                 std::map<float, float>* numbers) override;
};

#endif