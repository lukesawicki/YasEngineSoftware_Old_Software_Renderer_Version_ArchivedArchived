#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "game_object.hpp"

class Circle : public GameObject {
 private:
  bool is_direction_switched_;

 public:
  Circle(float radius, float x, float y);
  ~Circle();
  void Move(float deltaTime) override;
  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribedCircleRadius,
                                      int numberOfVertices) override;
  void RegeneratePolygon() override;
};

#endif
