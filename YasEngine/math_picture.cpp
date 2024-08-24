#include "math_picture.hpp"

MathPicture::MathPicture(std::map<int, float>* numbers,
                         PointsGenerator* points_Generator) {
  this->base_points_fuel_ = static_cast<int>(numbers->size());
  this->points_generator_ = points_Generator;
  this->numbers_ = numbers;
  this->float_numbers_ = nullptr;
  GeneratePoints();
}

MathPicture::MathPicture(std::map<float, float>* float_numbers,
                         PointsGenerator* points_generator) {
  this->base_points_fuel_ = static_cast<int>(float_numbers->size());
  this->points_generator_ = points_generator;
  this->numbers_ = nullptr;
  this->float_numbers_ = float_numbers;
  GeneratePoints();
}

MathPicture::~MathPicture() {
  delete points_generator_;
  delete numbers_;
  delete float_numbers_;
}

void MathPicture::GeneratePoints() {
  if (numbers_ != nullptr) {
    points_set_ = points_generator_->GeneratePoints(
        static_cast<int>(numbers_->size()), numbers_);
  }
  if (float_numbers_ != nullptr) {
    points_set_ = points_generator_->GenerateFloatPoints(
        static_cast<int>(float_numbers_->size()), float_numbers_);
  }
}
