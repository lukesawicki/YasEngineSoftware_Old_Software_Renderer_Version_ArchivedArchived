#ifndef PIXELSTABLE_HPP
#define PIXELSTABLE_HPP
#include <SDL.h>

#include "vector_2d.hpp"
#include "vector_4d.hpp"

class PixelsTable {
 public:
  Uint8* pixels_ = nullptr;
  Vector2D<int> window_dimensions_;
  PixelsTable(int width, int height, const Vector4D<Uint8>& defaultColor);
  PixelsTable(const PixelsTable& originalPixelsTable,
              const Vector4D<Uint8>& defaultColor);
  ~PixelsTable();
  void clearColor(const Vector4D<Uint8>& drawingColor);
  void drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor);
  void cartesianPositionToWindow(int& x, int& y);
};

#endif
