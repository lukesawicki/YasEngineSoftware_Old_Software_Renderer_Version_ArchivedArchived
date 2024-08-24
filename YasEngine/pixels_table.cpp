#include "pixels_table.hpp"

#include "yas_graphics_library.hpp"

PixelsTable::PixelsTable(int width, int height,
                         const Vector4D<Uint8>& defaultColor) {
  this->window_dimensions_.x_ = width;
  this->window_dimensions_.y_ = height;
  this->pixels_ = new Uint8[window_dimensions_.x_ * window_dimensions_.y_ *
                            kNumberOfColors];
  clearColor(defaultColor);
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

void PixelsTable::clearColor(const Vector4D<Uint8>& drawingColor) {
  for (int y = 0; y < window_dimensions_.y_; y++) {
    for (int x = 0; x < window_dimensions_.x_; x++) {
      pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
              kRedPosition] = drawingColor.x_;
      pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
              kGreenPosition] = drawingColor.y_;
      pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
              kBluePosition] = drawingColor.z_;
      pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
              kAlphaPosition] = drawingColor.w_;
    }
  }
}

void PixelsTable::drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor) {
  cartesianPositionToWindow(x, y);
  if (x >= 0 && x < window_dimensions_.x_ && y >= 0 &&
      y < window_dimensions_.y_) {
    pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) + kRedPosition] =
        drawingColor.x_;
    pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
            kGreenPosition] = drawingColor.y_;
    pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) + kBluePosition] =
        drawingColor.z_;
    pixels_[kNumberOfColors * (y * window_dimensions_.x_ + x) +
            kAlphaPosition] = drawingColor.w_;
  }
}

void PixelsTable::cartesianPositionToWindow(int& x, int& y) {
  x = x + static_cast<int>(0.5F * window_dimensions_.x_);
  y = -y + static_cast<int>(0.5F * window_dimensions_.y_);
}
