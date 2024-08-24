#ifndef MATHEMATICSFUNSURFACE_HPP
#define MATHEMATICSFUNSURFACE_HPP
#include "pixels_table.hpp"
#include "viewport.hpp"

class MathematicsGraphsSurface final : public ViewPort {
 public:
  void Render(double& deltaTime);

  void CartesianPositionToWindow(int& x, int& y) const {
    x = x + static_cast<int>(0.5F * view_port_sizes_.x_);
    y = -y + static_cast<int>(0.5F * view_port_sizes_.y_);
  }

  MathematicsGraphsSurface(int x, int y, int width, int height,
                           const Vector4D<Uint8>& default_color);
  MathematicsGraphsSurface(Vector2D<int> position, int width, int height,
                           const Vector4D<Uint8>& default_color);
  virtual ~MathematicsGraphsSurface();
  void ClearColor(const Vector4D<Uint8>& drawing_color) override;
  void DrawPoint(int x, int y, const Vector4D<Uint8>& drawing_color) override;
  void DrawLine(const Vector2D<float>& point_0, const Vector2D<float>& point_1,
                const Vector4D<Uint8>& drawing_color) override;
  void DrawPolygon(GameObject* polygon) override;
  void CopyPixelsInToPIxelTable(PixelsTable& pixels_table);
  void DrawNumbersAsGroupOfLines(Vector2D<float>* vertices,
                                 int maximum_number_of_vertices,
                                 int& current_number_of_vertices,
                                 const Vector4D<Uint8>& color,
                                 bool are_lines_continuous);

  void HorizontalLineOnSurface(int y, Vector4D<Uint8> color) {
    int maxX = static_cast<int>(0.5F * view_port_sizes_.x_);
    for (int i = -maxX; i < maxX; i++) {
      // X

      DrawPoint(i, y, color);
    }
  }

  void VerticalLineOnSurface(int x, Vector4D<Uint8> color) {
    int maxY = static_cast<int>(0.5F * view_port_sizes_.y_);
    for (int i = -maxY; i < maxY; i++) {
      // X
      DrawPoint(x, i, color);
    }
  }

  void DrawCartesianAxies();
};

#endif
