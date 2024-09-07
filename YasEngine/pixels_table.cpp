#include "pixels_table.hpp"

#include "yas_graphics_library.hpp"

PixelsTable::PixelsTable(int width, int height,
                         const Color& default_color) {
  window_dimensions_.width = width;
  window_dimensions_.height = height;
  pixels_ = new Uint8[window_dimensions_.width * window_dimensions_.height *
                            kNumberOfColors];
  ClearColor(default_color);
}

PixelsTable::PixelsTable(const PixelsTable& original_pixels_table,
                         const Color& default_color) {
  window_dimensions_.width = original_pixels_table.window_dimensions_.width;
  window_dimensions_.height = original_pixels_table.window_dimensions_.height;
  pixels_ =
      new Uint8[original_pixels_table.window_dimensions_.width *
                      original_pixels_table.window_dimensions_.height *
                      kNumberOfColors];
  for (int i = 0; i < window_dimensions_.width * window_dimensions_.height *
                          kNumberOfColors;
       i++) {
    pixels_[i] = original_pixels_table.pixels_[i];
  }
}

PixelsTable::~PixelsTable() { delete[] pixels_; }

void PixelsTable::ClearColor(const Color& drawing_color) {
  for (int y = 0; y < window_dimensions_.height; y++) {
    for (int x = 0; x < window_dimensions_.width; x++) {
      pixels_[kNumberOfColors * (y * window_dimensions_.width + x) +
              kRedPosition] = drawing_color.red;
      pixels_[kNumberOfColors * (y * window_dimensions_.width + x) +
              kGreenPosition] = drawing_color.green;
      pixels_[kNumberOfColors * (y * window_dimensions_.width + x) +
              kBluePosition] = drawing_color.blue;
      pixels_[kNumberOfColors * (y * window_dimensions_.width + x) +
              kAlphaPosition] = drawing_color.alpha;
    }
  }
}

void PixelsTable::DrawPoint(int x, int y, const Color& drawing_color) {
  CartesianPositionToWindow(x, y);
  if (x >= 0 && x < window_dimensions_.width && y >= 0 &&
      y < window_dimensions_.height) {
    pixels_[kNumberOfColors * (y * window_dimensions_.width + x) +
            kRedPosition] =
        drawing_color.red;
    pixels_[kNumberOfColors * (y * window_dimensions_.width + x) +
            kGreenPosition] = drawing_color.green;
    pixels_[kNumberOfColors * (y * window_dimensions_.width + x) +
            kBluePosition] =
        drawing_color.blue;
    pixels_[kNumberOfColors * (y * window_dimensions_.width + x) +
            kAlphaPosition] = drawing_color.alpha;
  }
}

void PixelsTable::CartesianPositionToWindow(int& x, int& y) {
  x = x + static_cast<int>(0.5F * window_dimensions_.width);
  y = -y + static_cast<int>(0.5F * window_dimensions_.height);
}
