#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "dimensions_2d.hpp"
#include "game_object.hpp"
#include "input_output_handler.hpp"

class Player : public GameObject {
 public:
  bool is_shooting_;
  int projectile_position_shift_ = 22;

  YasInOut::Input* input_;
  YasInOut::MousePositionChangeInformation* mouse_;

  float player_direction_angle_ = 90.0F * (3.141592F / 180.0F);
  float player_current_direction_angle_ = 0.0F;
  const Vector2D kx_direction_vector_ = Vector2D(1.0F, 0.0F);
  Vector2D look_at_ = Vector2D(1.0F, 0.0F);
  Vector2D current_mouse_angle_vector_;

  Player(float x, float y);
  ~Player();
  void Move(float delta_time) override;
  void RotateAllVerticesOverAnAngle(float angle);
  void Rotate(float delta_time);

  void RotateToMousePosition(float x, float y, Dimensions2D* window_dimensions);
  void RotateToMousePositionInLocalCoordinateSystem(
      float x, float y, Dimensions2D* window_dimensions);
  void set_direction(float x, float y);
  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                      int number_of_vertices) override;
  void RegeneratePolygon() override;
  void set_input(YasInOut::Input* input);
  void set_input(YasInOut::MousePositionChangeInformation* mouse);

};

#endif
