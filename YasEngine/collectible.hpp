#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP

#include "game_object.hpp"

class Collectible : public GameObject {
 public:
  Collectible(float radius, float x, float y, int number_of_vertices);
  ~Collectible();
  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                      int number_of_vertices) override;
  void RegeneratePolygon() override;
  void set_position(float x, float y);
  void set_position(const Vector2D<float>& position) override;
  void Move(float delta_time) override;
  void set_color(const Vector4D<Uint8>& color) override;
  void SetRandomColor();
};

#endif