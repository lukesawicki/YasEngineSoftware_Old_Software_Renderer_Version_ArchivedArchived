#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP
#include "game_object.hpp"
#include "vector_2d.hpp"
#include "vector_4d.hpp"

// Point of origin is on bottom left
class DrawingSurface {
 public:
  Vector2D position_;
  Dimensions2D view_port_sizes_;
  Uint8* pixels_ = nullptr;

  virtual void ClearColor(const Color& drawing_color) = 0;
  virtual void DrawPoint(int x, int y, const Color& drawing_color) = 0;
  virtual void DrawLine(const Vector2D& point_0,
                        const Vector2D& point_1,
                        const Color& drawing_color) = 0;
  virtual void DrawPolygon(GameObject* polygon) = 0;
};

#endif
