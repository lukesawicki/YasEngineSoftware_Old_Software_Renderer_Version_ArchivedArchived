#ifndef PIXELSTABLE_HPP
#define PIXELSTABLE_HPP
#include <SDL.h>

#include "vector_2d.hpp"
#include "vector_4d.hpp"

class PixelsTable {
 public:
  Uint8* pixels_ = nullptr;
  Vector2D<int> window_dimensions_;
  PixelsTable(int width, int height, const Vector4D<Uint8>& default_color);
  PixelsTable(const PixelsTable& original_pixels_table,
              const Vector4D<Uint8>& default_color);
  ~PixelsTable();
  void ClearColor(const Vector4D<Uint8>& drawing_color);
  void DrawPoint(int x, int y, const Vector4D<Uint8>& drawing_color);
  void CartesianPositionToWindow(int& x, int& y);
};

#endif
