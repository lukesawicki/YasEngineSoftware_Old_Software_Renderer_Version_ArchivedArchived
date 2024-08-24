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
  void Initialize();
  void InitializeFontObjects();
  void InitializeFontSurfaces();
  void PrepareFontVertices();
  void Write(int x, int y, std::string text, const Vector4D<Uint8>& color,
             PixelsTable& pixels_table);
  void Initialize(int character_width, int character_height,
                  const char* file_with_characters);
  void WriteNew(int x, int y, std::string text, int width, int height);
};

#endif  // SCREENWRITER_HPP
