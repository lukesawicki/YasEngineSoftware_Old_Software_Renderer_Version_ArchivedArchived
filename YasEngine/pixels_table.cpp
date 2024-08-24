#include "pixels_table.hpp"

#include "yas_graphics_library.hpp"

PixelsTable::PixelsTable(int width, int height,
                         const Vector4D<Uint8>& default_color) {
  this->window_dimensions_.x_ = width;
  this->window_dimensions_.y_ = height;
  this->pixels_ = new Uint8[window_dimensions_.x_ * window_dimensions_.y_ *
                            kNumberOfColors];
  ClearColor(default_color);
}

PixelsTable::PixelsTable(const PixelsTable& originalPixelsTable,
                         const Vector4D<Uint8>& defaultColor) {
  this->window_dimensions_.x_ = originalPixelsTable.window_dimensions_.x_;
  this->window_dimensions_.y_ = originalPixelsTable.window_dimensions_.y_;
  this->pixels_ =
      new Uint8[originalPixelsTable.window_dimensions_.x_ *
                originalPixelsTable.window_dimensions_.y_ * kNumberOfColors];
  for (int i = 0;
       i < window_dimensions_.x_ * window_dimensions_.y_ * kNumberOfColors;
       i++) {
    this->pixels_[i] = originalPixelsTable.pixels_[i];
  }
}

PixelsTable::~PixelsTable() { delete[] pixels_; }

void PixelsTable::ClearColor(const Vector4D<Uint8>& drawing_color) {
  for (int y = 0; y < window_dimensions_.y_; y++) {
    for (int x = 0; x < window_dimensions_.x_; x++) {
      pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
              kRedPosition] = drawing_color.x_;
      pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
              kGreenPosition] = drawing_color.y_;
      pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
              kBluePosition] = drawing_color.z_;
      pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
              kAlphaPosition] = drawing_color.w_;
    }
  }
}

void PixelsTable::DrawPoint(int x, int y, const Vector4D<Uint8>& drawing_color) {
  CartesianPositionToWindow(x, y);
  if (x >= 0 && x < window_dimensions_.x_ && y >= 0 &&
      y < window_dimensions_.y_) {
    pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) + kRedPosition] =
        drawing_color.x_;
    pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
            kGreenPosition] = drawing_color.y_;
    pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) + kBluePosition] =
        drawing_color.z_;
    pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
            kAlphaPosition] = drawing_color.w_;
  }
}

void PixelsTable::CartesianPositionToWindow(int& x, int& y) {
  x = x + static_cast<int>(0.5F * window_dimensions_.x_);
  y = -y + static_cast<int>(0.5F * window_dimensions_.y_);
}
