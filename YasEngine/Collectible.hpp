#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP

#include "game_object.hpp"

// Class which represent collectible
/**
 * Collectibles are derived from GameObject
 */
class Collectible : public GameObject {
 public:
  Collectible(float radius, float x, float y, int numberOfVertices);
  ~Collectible();
  void generate() override;
  void generateRegularPolygonVertices(float circumscribedCircleRadius,
                                      int numberOfVertices) override;
  void regeneratePolygon() override;
  void setPosition(float x, float y);
  void setPosition(const Vector2D<float>& position) override;
  void Move(float deltaTime) override;
  void setColor(const Vector4D<Uint8>& color) override;
  void setRandomColor();
};

#endif
