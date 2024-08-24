#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP
#include "game_object.hpp"
#include "vector_2d.hpp"
#include "vector_4d.hpp"

// Point of origin is on bottom left
class ViewPort {
 public:
  Vector2D<int> position_;
  Vector2D<int> view_port_sizes_;
  Uint8* pixels_ = nullptr;

  virtual void ClearColor(const Vector4D<Uint8>& drawing_color) = 0;
  virtual void DrawPoint(int x, int y, const Vector4D<Uint8>& drawing_color) = 0;
  virtual void DrawLine(const Vector2D<float>& point_0,
                        const Vector2D<float>& point_1,
                        const Vector4D<Uint8>& drawing_color) = 0;
  virtual void DrawPolygon(GameObject* polygon) = 0;
};

#endif
