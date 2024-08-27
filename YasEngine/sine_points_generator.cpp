#include "sine_points_generator.hpp"

#include "yas_graphics_library.hpp"

SinePointsGenerator::~SinePointsGenerator() { ; }

PointsSet* SinePointsGenerator::GeneratePoints(int number_of_numbers,
                                               std::map<int, float>* numbers) {
  this->points_number_ = number_of_numbers;
  Vector2D<float>* points = new Vector2D<float>[points_number_];
  float divider = static_cast<float>(points_number_);
  float maximum_x_value = 2.0F * kPi;
  float additional_factor = 50.0F;
  float step = (maximum_x_value / divider);

  for (int i = 0; i < points_number_; i++) {
    float x = i * step;
    float y = sin(x);

    // numbers.push_back(y_);

    points[i].x_ = x * additional_factor;  // round(x_ * additionalFactor);
    points[i].y_ = y * additional_factor;  // round(y_ * additionalFactor);
  }

  PointsSet* points_set = new PointsSet();
  points_set->points_ = points;
  points_set->points_number_ = points_number_;
  return points_set;
}

PointsSet* SinePointsGenerator::GenerateFloatPoints(
    int number_of_numbers, std::map<float, float>* numbers) {
  this->points_number_ = number_of_numbers;
  Vector2D<float>* points = new Vector2D<float>[points_number_];
  int additional_factor = 50;
  int i = 0;
  for (std::pair<float, float> pair : *numbers) {
    points[i].x_ =
        pair.first * additional_factor;  // round(x_ * additionalFactor);
    points[i].y_ =
        pair.second * additional_factor;  // round(y_ * additionalFactor);
    i++;
  }

  PointsSet* points_set = new PointsSet();
  points_set->points_ = points;
  points_set->points_number_ = points_number_;
  return points_set;
}