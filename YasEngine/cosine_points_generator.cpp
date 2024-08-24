#include "cosine_points_generator.hpp"

#include "yas_graphics_library.hpp"

CosinePointsGenerator::~CosinePointsGenerator() { ; }

PointsSet* CosinePointsGenerator::generatePoints(
    int numberOfNumbers, std::map<int, float>* numbers) {
  this->points_number_ = numberOfNumbers;
  Vector2D<float>* points = new Vector2D<float>[points_number_];
  float divider = static_cast<float>(points_number_);
  float maximumXvalue = 2.0F * kPi;
  float additionalFactor = 50.0F;
  float step = (maximumXvalue / divider);

  for (int i = 0; i < points_number_; i++) {
    float x = i * step;
    float y = cos(x);
    points[i].x_ = round(x * additionalFactor);
    points[i].y_ = round(y * additionalFactor);
  }

  PointsSet* pointsSet = new PointsSet();
  pointsSet->points_ = points;
  pointsSet->points_number_ = points_number_;
  return pointsSet;
}

PointsSet* CosinePointsGenerator::generateFloatPoints(
    int numberOfNumbers, std::map<float, float>* numbers) {
  this->points_number_ = numberOfNumbers;
  Vector2D<float>* points = new Vector2D<float>[points_number_];
  int additionalFactor = 50;
  int i = 0;
  for (std::pair<float, float> pair : *numbers) {
    points[i].x_ = pair.first * additionalFactor;
    points[i].y_ = pair.second * additionalFactor;
    i++;
  }

  PointsSet* pointsSet = new PointsSet();
  pointsSet->points_ = points;
  pointsSet->points_number_ = points_number_;
  return pointsSet;
}
