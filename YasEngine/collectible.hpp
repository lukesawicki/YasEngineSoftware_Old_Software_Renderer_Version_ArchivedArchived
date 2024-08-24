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
  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribedCircleRadius,
                                      int numberOfVertices) override;
  void RegeneratePolygon() override;
  void set_position(float x, float y);
  void set_position(const Vector2D<float>& position) override;
  void Move(float deltaTime) override;
  void set_color(const Vector4D<Uint8>& color) override;
  void SetRandomColor();
};

#endif
