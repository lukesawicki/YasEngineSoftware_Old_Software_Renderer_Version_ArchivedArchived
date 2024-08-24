#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "game_object.hpp"
#include "time_picker.hpp"

class Projectile : public GameObject {
 public:
  int live_time_ = 500;
  TimePicker time_picker_;

  double start_time_ = 0;
  double current_time_ = 0;

  Vector2D<float> velocity_;
  Projectile(float radius, float x, float y, Vector2D<float> direction);
  ~Projectile();
  void Move(float delta_time) override;
  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                      int number_of_vertices) override;
  void RegeneratePolygon() override;
};

#endif
