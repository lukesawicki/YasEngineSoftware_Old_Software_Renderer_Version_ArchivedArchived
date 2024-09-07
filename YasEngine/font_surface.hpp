#ifndef FONT_SURFACE_HPP
#define FONT_SURFACE_HPP
#include "pixels_table.hpp"
#include "DrawingSurface.hpp"
#include "yas_graphics_library.hpp"

class FontSurface : public DrawingSurface {
 public:
  void CartesianPositionToWindow(int& x, int& y) const {
    x = x + static_cast<int>(0.5F * view_port_sizes_.width);
    y = -y + static_cast<int>(0.5F * view_port_sizes_.height);
  }

  FontSurface();
  void Initialize(int x, int y, int width, int height,
                  const Color& default_color);
  virtual ~FontSurface();
  void ClearColor(const Color& drawing_color) override;
  void DrawPoint(int x, int y, const Color& drawing_color) override;
  void DrawLine(const Vector2D& point0, const Vector2D& point1,
                const Color& drawing_color) override;
  void DrawPolygon(GameObject* polygon) override;
  void CopyPixelsInToPIxelTable(PixelsTable& pixels_table);

  unsigned int CalculateMaximumNumberOfElementsToProcess(
      const unsigned int& primary_maximum, bool connected_lines);
  void DrawNumbersAsGroupOfLines(Vector2D* vertices,
                                 int maximum_number_of_vertices,
                                 const Color& color,
                                 bool are_lines_continuous);

  void HorizontalLineOnSurface(int y, Color color) {
    int maxX = static_cast<int>(0.5F * view_port_sizes_.width);
    for (int i = -maxX; i < maxX; i++) {
      // X

      DrawPoint(i, y, color);
    }
  }

  void VerticalLineOnSurface(int x, Color color) {
    int maxY = static_cast<int>(0.5F * view_port_sizes_.height);
    for (int i = -maxY; i < maxY; i++) {
      // X

      DrawPoint(x, i, color);
    }
  }

  void DrawCartesianAxies();
};

#endif
