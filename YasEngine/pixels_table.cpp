#include "pixels_table.hpp"

#include "yas_graphics_library.hpp"

PixelsTable::PixelsTable(int width, int height,
                         const Vector4D<Uint8>& defaultColor) {
  this->windowDimensions.x = width;
  this->windowDimensions.y = height;
  this->pixels =
      new Uint8[windowDimensions.x * windowDimensions.y * kNumberOfColors];
  clearColor(defaultColor);
}

PixelsTable::PixelsTable(const PixelsTable& originalPixelsTable,
                         const Vector4D<Uint8>& defaultColor) {
  this->windowDimensions.x = originalPixelsTable.windowDimensions.x;
  this->windowDimensions.y = originalPixelsTable.windowDimensions.y;
  this->pixels =
      new Uint8[originalPixelsTable.windowDimensions.x *
                originalPixelsTable.windowDimensions.y * kNumberOfColors];
  for (int i = 0; i < windowDimensions.x * windowDimensions.y * kNumberOfColors;
       i++) {
    this->pixels[i] = originalPixelsTable.pixels[i];
  }
}

PixelsTable::~PixelsTable() { delete[] pixels; }

void PixelsTable::clearColor(const Vector4D<Uint8>& drawingColor) {
  for (int y = 0; y < windowDimensions.y; y++) {
    for (int x = 0; x < windowDimensions.x; x++) {
      pixels[kNumberOfColors * (y * windowDimensions.x + x) + kRedPosition] =
          drawingColor.x;
      pixels[kNumberOfColors * (y * windowDimensions.x + x) + kGreenPosition] =
          drawingColor.y;
      pixels[kNumberOfColors * (y * windowDimensions.x + x) + kBluePosition] =
          drawingColor.z;
      pixels[kNumberOfColors * (y * windowDimensions.x + x) + kAlphaPosition] =
          drawingColor.w;
    }
  }
}

void PixelsTable::drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor) {
  cartesianPositionToWindow(x, y);
  if (x >= 0 && x < windowDimensions.x && y >= 0 && y < windowDimensions.y) {
    pixels[kNumberOfColors * (y * windowDimensions.x + x) + kRedPosition] =
        drawingColor.x;
    pixels[kNumberOfColors * (y * windowDimensions.x + x) + kGreenPosition] =
        drawingColor.y;
    pixels[kNumberOfColors * (y * windowDimensions.x + x) + kBluePosition] =
        drawingColor.z;
    pixels[kNumberOfColors * (y * windowDimensions.x + x) + kAlphaPosition] =
        drawingColor.w;
  }
}

void PixelsTable::cartesianPositionToWindow(int& x, int& y) {
  x = x + static_cast<int>(0.5F * windowDimensions.x);
  y = -y + static_cast<int>(0.5F * windowDimensions.y);
}
