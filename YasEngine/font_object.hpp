#ifndef YASENGINESOFTWARE_FONTOBJECT_HPP
#define YASENGINESOFTWARE_FONTOBJECT_HPP

#include "game_object.hpp"

class FontObject : public GameObject {
 public:
  FontObject();
  void initialize(float radius, float x, float y,
                  const Vector2D<float>& direction, int numberOfVertices);
  virtual ~FontObject();
  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribedCircleRadius,
                                      int numberOfVertices) override;
  void RegeneratePolygon() override;
  void setPosition(float x, float y);
  void set_position(const Vector2D<float>& position) override;
  void Move(float deltaTime) override;
  void set_color(const Vector4D<Uint8>& color) override;
  void setRandomColor();
  Vector2D<float> velocity_;
};

#endif  // YASENGINESOFTWARE_FONTOBJECT_HPP
