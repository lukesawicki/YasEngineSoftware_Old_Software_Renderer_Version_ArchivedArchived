#ifndef PRIMENUMBERSPOINTSGENERATOR_HPP
#define PRIMENUMBERSPOINTSGENERATOR_HPP
#include <map>

#include "mathematics.hpp"
#include "points_generator.hpp"
#include "Points_2d_Set.hpp"

class PrimeNumbersPointsGenerator : public PointsGenerator {
 public:
  static std::vector<int> numbers_;
  ~PrimeNumbersPointsGenerator();
  Points_2d_Set* GeneratePoints(int number_of_numbers,
                            std::map<int, float>* numbers) override;
  Points_2d_Set* GenerateFloatPoints(int number_of_numbers,
                                 std::map<float, float>* numbers) override;
};

#endif