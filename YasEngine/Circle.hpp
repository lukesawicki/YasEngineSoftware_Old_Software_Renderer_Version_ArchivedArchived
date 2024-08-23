#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "game_object.hpp"

class Circle : public GameObject {
 private:
  bool directionSwitched;

 public:
  Circle(float radius, float x, float y);
  ~Circle();
  void Move(float deltaTime) override;
  void generate() override;
  void generateRegularPolygonVertices(float circumscribedCircleRadius,
                                      int numberOfVertices) override;
  void regeneratePolygon() override;
};

#endif
