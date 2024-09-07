#ifndef PIXELSTABLE_HPP
#define PIXELSTABLE_HPP
#include <SDL.h>

#include "color.hpp"
#include "dimensions_2d.hpp"


class PixelsTable {
 public:
  Uint8* pixels_ = nullptr;
  Dimensions2D window_dimensions_;
  PixelsTable(int width, int height, const Color& default_color);
  PixelsTable(const PixelsTable& original_pixels_table,
              const Color& default_color);
  ~PixelsTable();
  void ClearColor(const Color& drawing_color);
  void DrawPoint(int x, int y, const Color& drawing_color);
  void CartesianPositionToWindow(int& x, int& y);
};

#endif
