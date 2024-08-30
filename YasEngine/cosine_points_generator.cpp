#include "cosine_points_generator.hpp"

#include "yas_graphics_library.hpp"

CosinePointsGenerator::~CosinePointsGenerator() { ; }

Points_2d_Set* CosinePointsGenerator::GeneratePoints(
    int number_of_numbers, std::map<int, float>* numbers) {
  this->points_number_ = number_of_numbers;
  Vector2D<float>* points = new Vector2D<float>[points_number_];
  float divider = static_cast<float>(points_number_);
  float maximum_x_value = 2.0F * kPi;
  float additional_factor = 50.0F;
  float step = (maximum_x_value / divider);

  for (int i = 0; i < points_number_; i++) {
    float x = i * step;
    float y = cos(x);
    points[i].x_ = round(x * additional_factor);
    points[i].y_ = round(y * additional_factor);
  }

  Points_2d_Set* points_set = new Points_2d_Set();
  points_set->points_ = points;
  points_set->points_number_ = points_number_;
  return points_set;
}

Points_2d_Set* CosinePointsGenerator::GenerateFloatPoints(
    int number_of_numbers, std::map<float, float>* numbers) {
  this->points_number_ = number_of_numbers;
  Vector2D<float>* points = new Vector2D<float>[points_number_];
  int additional_factor = 50;
  int i = 0;
  for (std::pair<float, float> pair : *numbers) {
    points[i].x_ = pair.first * additional_factor;
    points[i].y_ = pair.second * additional_factor;
    i++;
  }

  Points_2d_Set* points_set = new Points_2d_Set();
  points_set->points_ = points;
  points_set->points_number_ = points_number_;
  return points_set;
}
