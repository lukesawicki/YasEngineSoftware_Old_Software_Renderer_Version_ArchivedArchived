#include "prime_numbers_points_generator.hpp"

#include "yas_graphics_library.hpp"

PrimeNumbersPointsGenerator::~PrimeNumbersPointsGenerator() { ; }

PointsSet* PrimeNumbersPointsGenerator::generatePoints(
    int numberOfNumbers, std::map<int, float>* numbers) {
  this->points_number_ = numberOfNumbers;

  Vector2D<float>* points = new Vector2D<float>[points_number_ * 2];

  int j = 0;
  for (int i = 1; i < (points_number_ * 2) - 1; i += 2) {
    // float n = // (*numbers).at(i);
    points[i].x = numbers->at(j++);  // primeNumbers.at(j++));//100.0F; //
                                     // static_cast<float>(fibonacci.at(j++));
  }

  j = 0;
  for (int i = 1; i < points_number_ * 2 - 1; i += 2) {
    Vector2D<float>::rotateVectorOverTheAngle(
        &points[i], static_cast<int>(numbers->at(j++)) * (kPi / 180.0F));
  }

  PointsSet* pointsSet = new PointsSet();
  pointsSet->points = points;
  pointsSet->pointsNumber = points_number_;
  return pointsSet;
}

PointsSet* PrimeNumbersPointsGenerator::generateFloatPoints(
    int numberOfNumbers, std::map<float, float>* numbers) {
  return nullptr;
}
