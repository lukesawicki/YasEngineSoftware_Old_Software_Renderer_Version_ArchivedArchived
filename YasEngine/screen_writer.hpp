#ifndef SCREENWRITER_HPP
#define SCREENWRITER_HPP
#include <SDL.h>

#include <string>
#include <vector>

#include "font_object.hpp"
#include "font_surface.hpp"

class ScreenWriter final {
 public:
  static const int knumber_of_characters = 37;
  static const int kfont_width = 17;
  static const int kfont_height = 17;

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
  char characters_table_[knumber_of_characters];
  ScreenWriter();
  void initialize();
  void initializeFontObjects();
  void initializeFontSurfaces();
  void prepareFontVertices();
  void write(int x, int y, std::string text, const Vector4D<Uint8>& color,
             PixelsTable& pixelsTable);
  void initialize(int characterWidth, int characterHeight,
                  const char* plik_znakow);
  void writeNew(int x, int y, std::string text, int width, int height);
};

#endif  // SCREENWRITER_HPP
