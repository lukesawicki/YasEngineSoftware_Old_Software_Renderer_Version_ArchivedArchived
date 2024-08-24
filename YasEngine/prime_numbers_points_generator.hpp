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
  PointsSet* GeneratePoints(int number_of_numbers,
                            std::map<int, float>* numbers) override;
  PointsSet* GenerateFloatPoints(int number_of_numbers,
                                 std::map<float, float>* numbers) override;
};

#endif