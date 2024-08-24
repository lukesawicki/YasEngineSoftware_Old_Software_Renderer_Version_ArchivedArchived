#include "fibonacci_points_generator.hpp"

#include "mathematics.hpp"
#include "yas_graphics_library.hpp"

FibonacciPointsGenerator::~FibonacciPointsGenerator() { ; }

PointsSet* FibonacciPointsGenerator::generatePoints(
    int numberOfNumbers, std::map<int, float>* numbers) {
  // 40
  this->points_number_ = numberOfNumbers;

  Vector2D<float>* points = new Vector2D<float>[points_number_ * 2];
  std::vector<int> fibonacci = generateNfibonacciNumbers(points_number_);

  // Point constructor setting x_ and y_ to 0;
  // This loop creates pairs of points_ = ( (0,0) ; (fibonacci(i) ,y_=0) )
  int j = 0;
  for (int i = 1; i < (points_number_ * 2) - 1; i += 2) {
    points[i].x_ = static_cast<float>(fibonacci.at(
        j++));  // 100.0F; // static_cast<float>(fibonacci.at(j++));
  }

  // DLUGOSC LINI JEST TEZ FIBONACCI NARAZIE
  // ALE WIECEJ LINI BEDZIE JESLI DLUGOSCI ZROBIE STALE
  j = 0;
  for (int i = 1; i < points_number_ * 2 - 1; i += 2) {
    Vector2D<float>::rotateVectorOverTheAngle(
        &points[i], fibonacci.at(j++) * (kPi / 180.0F));
  }

  PointsSet* pointsSet = new PointsSet();
  pointsSet->points_ = points;

  pointsSet->points_number_ = points_number_;

  return pointsSet;
}

PointsSet* FibonacciPointsGenerator::generateFloatPoints(
    int numberOfNumbers, std::map<float, float>* numbers) {
  return nullptr;
}
