#include "fibonacci_points_generator.hpp"

#include "mathematics.hpp"
#include "yas_graphics_library.hpp"

FibonacciPointsGenerator::~FibonacciPointsGenerator() { ; }

PointsSet* FibonacciPointsGenerator::GeneratePoints(
    int number_of_numbers, std::map<int, float>* numbers) {
  // 40
  this->points_number_ = number_of_numbers;

  Vector2D<float>* points = new Vector2D<float>[points_number_ * 2];
  std::vector<int> fibonacci_numbers = GenerateNfibonacciNumbers(points_number_);

  // Point constructor setting x_ and y_ to 0;
  // This loop creates pairs of points_ = ( (0,0) ; (fibonacci(i) ,y_=0) )
  int j = 0;
  for (int i = 1; i < (points_number_ * 2) - 1; i += 2) {
    points[i].x_ = static_cast<float>(fibonacci_numbers.at(
        j++));  // 100.0F; // static_cast<float>(fibonacci.at(j++));
  }

  // DLUGOSC LINI JEST TEZ FIBONACCI NARAZIE
  // ALE WIECEJ LINI BEDZIE JESLI DLUGOSCI ZROBIE STALE
  j = 0;
  for (int i = 1; i < points_number_ * 2 - 1; i += 2) {
    Vector2D<float>::RotateVectorOverTheAngle(
        &points[i], fibonacci_numbers.at(j++) * (kPi / 180.0F));
  }

  PointsSet* points_set = new PointsSet();
  points_set->points_ = points;

  points_set->points_number_ = points_number_;

  return points_set;
}

PointsSet* FibonacciPointsGenerator::GenerateFloatPoints(
    int number_of_numbers, std::map<float, float>* numbers) {
  return nullptr;
}
