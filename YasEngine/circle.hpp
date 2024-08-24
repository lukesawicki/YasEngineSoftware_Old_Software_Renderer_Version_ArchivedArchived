#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "game_object.hpp"

class Circle : public GameObject {
 private:
  bool is_direction_switched_;

 public:
  Circle(float radius, float x, float y);
  ~Circle();
  void Move(float delta_time) override;
  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                      int number_of_vertices) override;
  void RegeneratePolygon() override;
};

#endif
