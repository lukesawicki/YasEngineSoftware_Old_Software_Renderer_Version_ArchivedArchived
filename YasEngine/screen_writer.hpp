#ifndef SCREENWRITER_HPP
#define SCREENWRITER_HPP
#include <SDL.h>

#include <string>
#include <vector>

#include "font_object.hpp"
#include "font_surface.hpp"

class ScreenWriter {
 public:
  static const int knumber_of_characters_ = 37;
  static const int kfont_width_ = 17;
  static const int kfont_height_ = 17;
  static const int kfont_top_margin_height_ = 2;
  static const int kfont_bottom_margin_height_ = 2;
  int max_characters_horizontally_;
  int max_characters_vertically_;
  int* vertical_top_positions_;
  int top_max;
  int* vertical_bottom_positions_;
  int top_bottom;

  struct Font {
    Font() {
      verticesBaseData = new FontObject();
      surface = new FontSurface();
    }

    ~Font() {
      delete verticesBaseData;
      delete surface;
    }

    FontObject* verticesBaseData;
    FontSurface* surface;
  };

  std::vector<Font*> fonts_;
  char characters_table_[knumber_of_characters_];
  ScreenWriter(const Vector2D<int>* window_dimensions);
  void Initialize();
  void InitializeFontObjects();
  void InitializeFontSurfaces();
  void PrepareFontVertices();
  void Write(int x, int y, std::string text, const Vector4D<Uint8>& color,
             PixelsTable& pixels_table);
};

#endif
