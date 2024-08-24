#include "prime_numbers_points_generator.hpp"

#include "yas_graphics_library.hpp"

PrimeNumbersPointsGenerator::~PrimeNumbersPointsGenerator() { ; }

PointsSet* PrimeNumbersPointsGenerator::GeneratePoints(
    int number_of_numbers, std::map<int, float>* numbers) {
  this->points_number_ = number_of_numbers;

  Vector2D<float>* points = new Vector2D<float>[points_number_ * 2];

  int j = 0;
  for (int i = 1; i < (points_number_ * 2) - 1; i += 2) {
    // float n = // (*numbers_).at(i);
    points[i].x_ = numbers->at(j++);  // primeNumbers.at(j++));//100.0F; //
                                      // static_cast<float>(fibonacci.at(j++));
  }

  j = 0;
  for (int i = 1; i < points_number_ * 2 - 1; i += 2) {
    Vector2D<float>::RotateVectorOverTheAngle(
        &points[i], static_cast<int>(numbers->at(j++)) * (kPi / 180.0F));
  }

  PointsSet* pointsSet = new PointsSet();
  pointsSet->points_ = points;
  pointsSet->points_number_ = points_number_;
  return pointsSet;
}

PointsSet* PrimeNumbersPointsGenerator::GenerateFloatPoints(
    int number_of_numbers, std::map<float, float>* numbers) {
  return nullptr;
}
