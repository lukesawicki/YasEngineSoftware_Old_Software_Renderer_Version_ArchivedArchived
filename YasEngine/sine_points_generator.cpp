#include "sine_points_generator.hpp"

#include "yas_graphics_library.hpp"

SinePointsGenerator::~SinePointsGenerator() { ; }

PointsSet* SinePointsGenerator::generatePoints(int numberOfNumbers,
                                               std::map<int, float>* numbers) {
  this->points_number_ = numberOfNumbers;
  Vector2D<float>* points = new Vector2D<float>[points_number_];
  float divider = static_cast<float>(points_number_);
  float maximumXvalue = 2.0F * kPi;
  float additionalFactor = 50.0F;
  float step = (maximumXvalue / divider);

  for (int i = 0; i < points_number_; i++) {
    float x = i * step;
    float y = sin(x);

    // numbers.push_back(y_);

    points[i].x_ = x * additionalFactor;  // round(x_ * additionalFactor);
    points[i].y_ = y * additionalFactor;  // round(y_ * additionalFactor);
  }

  PointsSet* pointsSet = new PointsSet();
  pointsSet->points_ = points;
  pointsSet->points_number_ = points_number_;
  return pointsSet;
}

PointsSet* SinePointsGenerator::generateFloatPoints(
    int numberOfNumbers, std::map<float, float>* numbers) {
  this->points_number_ = numberOfNumbers;
  Vector2D<float>* points = new Vector2D<float>[points_number_];
  int additionalFactor = 50;
  int i = 0;
  for (std::pair<float, float> pair : *numbers) {
    points[i].x_ =
        pair.first * additionalFactor;  // round(x_ * additionalFactor);
    points[i].y_ =
        pair.second * additionalFactor;  // round(y_ * additionalFactor);
    i++;
  }

  PointsSet* pointsSet = new PointsSet();
  pointsSet->points_ = points;
  pointsSet->points_number_ = points_number_;
  return pointsSet;
}