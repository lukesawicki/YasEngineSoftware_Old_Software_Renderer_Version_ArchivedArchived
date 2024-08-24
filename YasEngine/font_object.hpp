#ifndef YASENGINESOFTWARE_FONTOBJECT_HPP
#define YASENGINESOFTWARE_FONTOBJECT_HPP

#include "game_object.hpp"

class FontObject : public GameObject {
 public:
  FontObject();
  void initialize(float radius, float x, float y,
                  const Vector2D<float>& direction, int number_of_vertices);
  virtual ~FontObject();
  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                      int number_of_vertices) override;
  void RegeneratePolygon() override;
  void set_position(float x, float y);
  void set_position(const Vector2D<float>& position) override;
  void Move(float delta_time) override;
  void set_color(const Vector4D<Uint8>& color) override;
  void SetRandomColor();
  Vector2D<float> velocity_;
};

#endif  // YASENGINESOFTWARE_FONTOBJECT_HPP
