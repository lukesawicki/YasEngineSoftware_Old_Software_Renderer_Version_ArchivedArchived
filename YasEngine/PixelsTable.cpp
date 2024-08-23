#include"PixelsTable.hpp"
#include "YasGraphicsLibrary.hpp"

PixelsTable::PixelsTable(int width, int height, const Vector4D<Uint8>& defaultColor) {
  this->windowDimensions.x = width;
  this->windowDimensions.y = height;
  this->pixels = new Uint8[windowDimensions.x * windowDimensions.y * NUMBER_OF_COLORS];
  clearColor(defaultColor);
}

PixelsTable::PixelsTable(const PixelsTable& originalPixelsTable, const Vector4D<Uint8>& defaultColor) {
  this->windowDimensions.x = originalPixelsTable.windowDimensions.x;
  this->windowDimensions.y = originalPixelsTable.windowDimensions.y;
  this->pixels = new Uint8[originalPixelsTable.windowDimensions.x * originalPixelsTable.windowDimensions.y *
    NUMBER_OF_COLORS];
  for (int i = 0; i < windowDimensions.x * windowDimensions.y * NUMBER_OF_COLORS; i++) {
    this->pixels[i] = originalPixelsTable.pixels[i];
  }
}

PixelsTable::~PixelsTable() {
  delete[] pixels;
}

void PixelsTable::clearColor(const Vector4D<Uint8>& drawingColor) {
  for (int y = 0; y < windowDimensions.y; y++) {
    for (int x = 0; x < windowDimensions.x; x++) {
      pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + RED_POSITION] = drawingColor.x;
      pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + GREEN_POSITION] = drawingColor.y;
      pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + BLUE_POSITION] = drawingColor.z;
      pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + ALPHA_POSITION] = drawingColor.w;
    }
  }
}

void PixelsTable::drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor) {
  cartesianPositionToWindow(x, y);
  if (x >= 0 && x < windowDimensions.x && y >= 0 && y < windowDimensions.y) {
    pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + RED_POSITION] = drawingColor.x;
    pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + GREEN_POSITION] = drawingColor.y;
    pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + BLUE_POSITION] = drawingColor.z;
    pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + ALPHA_POSITION] = drawingColor.w;
  }
}

void PixelsTable::cartesianPositionToWindow(int& x, int& y) {
  x = x + static_cast<int>(0.5F * windowDimensions.x);
  y = -y + static_cast<int>(0.5F * windowDimensions.y);
}
