#ifndef YASENGINESOFTWARE_FONTOBJECT_HPP
#define YASENGINESOFTWARE_FONTOBJECT_HPP

#include "game_object.hpp"

class FontObject : public GameObject {
 public:
  FontObject();
  void initialize(float radius, float x, float y,
                  const Vector2D<float>& direction, int numberOfVertices);
  virtual ~FontObject();
  void generate() override;
  void generateRegularPolygonVertices(float circumscribedCircleRadius,
                                      int numberOfVertices) override;
  void regeneratePolygon() override;
  void setPosition(float x, float y);
  void setPosition(const Vector2D<float>& position) override;
  void move(float deltaTime) override;
  void setColor(const Vector4D<Uint8>& color) override;
  void setRandomColor();
  Vector2D<float> velocity_;
};

#endif  // YASENGINESOFTWARE_FONTOBJECT_HPP
