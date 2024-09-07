#ifndef YASENGINESOFTWARE_FONTOBJECT_HPP
#define YASENGINESOFTWARE_FONTOBJECT_HPP

#include "game_object.hpp"
#include "yas_graphics_library.hpp"

class FontObject : public GameObject {
 public:
  FontObject();
  void initialize(float radius, float x, float y,
                  const Vector2D& direction, int number_of_vertices);
  virtual ~FontObject();
  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                      int number_of_vertices) override;
  void RegeneratePolygon() override;
  void set_position(float x, float y);
  void set_position(const Vector2D& position) override;
  void Move(float delta_time) override;
  void set_color(const Color& color) override;
  void SetRandomColor();
  Vector2D velocity_;
};

#endif
