#include "math_picture.hpp"

MathPicture::MathPicture(std::map<int, float>* numbers,
                         PointsGenerator* pointsGenerator) {
  this->base_points_fuel_ = static_cast<int>(numbers->size());
  this->points_generator_ = pointsGenerator;
  this->numbers_ = numbers;
  this->float_numbers_ = nullptr;
  generatePoints();
}

MathPicture::MathPicture(std::map<float, float>* floatNumbers,
                         PointsGenerator* pointsGenerator) {
  this->base_points_fuel_ = static_cast<int>(floatNumbers->size());
  this->points_generator_ = pointsGenerator;
  this->numbers_ = nullptr;
  this->float_numbers_ = floatNumbers;
  generatePoints();
}

MathPicture::~MathPicture() {
  delete points_generator_;
  delete numbers_;
  delete float_numbers_;
}

void MathPicture::generatePoints() {
  if (numbers_ != nullptr) {
    points_set_ = points_generator_->generatePoints(
        static_cast<int>(numbers_->size()), numbers_);
  }
  if (float_numbers_ != nullptr) {
    points_set_ = points_generator_->generateFloatPoints(
        static_cast<int>(float_numbers_->size()), float_numbers_);
  }
}
