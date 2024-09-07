#include "player.hpp"

#include "yas_engine.hpp"
#include "yas_graphics_library.hpp"

Player::Player(float x, float y) {
  collider_.x_ = x;
  collider_.y_ = y;
  collider_.radius_ = 20;
  i_am_ = WhoAmI::kPlayer;
  position.x_ = x;
  position.y_ = y;

  direction_.x_ = 1;
  direction_.y_ = 0;

  speed_ = 200;
  rotation_speed_ = 5;

  number_of_vertices_ = 17;

  world_vertices_ = new Vector2D[number_of_vertices_];
  local_vertices_ = new Vector2D[number_of_vertices_];

  local_vertices_[0].x_ = -12;
  local_vertices_[0].y_ = -11;

  local_vertices_[1].x_ = -2;
  local_vertices_[1].y_ = -11;

  local_vertices_[2].x_ = 8;
  local_vertices_[2].y_ = -9;

  local_vertices_[3].x_ = -2;
  local_vertices_[3].y_ = -7;

  local_vertices_[4].x_ = -2;
  local_vertices_[4].y_ = -3;

  local_vertices_[5].x_ = 12;
  local_vertices_[5].y_ = 0;

  local_vertices_[6].x_ = -2;
  local_vertices_[6].y_ = 3;

  local_vertices_[7].x_ = -2;
  local_vertices_[7].y_ = 7;

  local_vertices_[8].x_ = 8;
  local_vertices_[8].y_ = 9;

  local_vertices_[9].x_ = -2;
  local_vertices_[9].y_ = 11;

  local_vertices_[10].x_ = -12;
  local_vertices_[10].y_ = 11;

  local_vertices_[11].x_ = -8;
  local_vertices_[11].y_ = 7;

  local_vertices_[12].x_ = -12;
  local_vertices_[12].y_ = 3;

  local_vertices_[13].x_ = -8;
  local_vertices_[13].y_ = 3;

  local_vertices_[14].x_ = -8;
  local_vertices_[14].y_ = -3;

  local_vertices_[15].x_ = -12;
  local_vertices_[15].y_ = -3;

  local_vertices_[16].x_ = -8;
  local_vertices_[16].y_ = -7;

  Generate();
}

Player::~Player() {
  delete[] world_vertices_;
  delete[] local_vertices_;
  // delete input_; // It will be deleted in YasEngine
  // delete mouse_; // It will be deleted in YasEngine
}

void Player::Move(float delta_time) {
  // LEFT
  if (input_->left && !input_->right) {
    position.x_ = position.x_ + delta_time * (-speed_);
  }

  // RIGHT
  if (input_->right && !input_->left) {
    position.x_ = position.x_ + delta_time * speed_;
  }

  // UP
  if (input_->up && !input_->down) {
    position.y_ = position.y_ + delta_time * speed_;
  }

  // DOWN
  if (input_->down && !input_->up) {
    position.y_ = position.y_ + delta_time * (-speed_);
  }

  MoveCollider();

  // SPACE
  if (input_->shoot || mouse_->left_mouse_button) {
    is_shooting_ = true;
  }
  RegeneratePolygon();
}

void Player::Rotate(float delta_time) {
  if (input_->rotate_counter_clockwise) {
    direction_mouse_angle_ = direction_mouse_angle_ * 3.141592F / 180.0F;
    direction_mouse_angle_ = delta_time * rotation_speed_;
    player_current_direction_angle_ =
        player_current_direction_angle_ + direction_mouse_angle_;
    if (player_current_direction_angle_ >= 6.28319F) {
      player_current_direction_angle_ =
          player_current_direction_angle_ - 6.28319F;
    }
    RotateAllVerticesOverAnAngle(direction_mouse_angle_);
    Generate();
  }
}

void Player::RotateToMousePosition(float x, float y,
                                   Dimensions2D* window_dimensions) {
  if (x <= window_dimensions->width && y <= window_dimensions->height) {
    float current_x = x;
    float current_y = y;

    WindowPositionToCartesianPosition(current_x, current_y, window_dimensions);

    Vector2D mousePositionVector(static_cast<float>(current_x),
                                        static_cast<float>(current_y));
    // Vector2D::NormalizedVector(mousePositionVector);

    float angle_between_current_and_mouse =
        Vector2D::AngleBetweenVectors(direction_, mousePositionVector);
    RotateAllVerticesOverAnAngle(angle_between_current_and_mouse);
    set_direction(mousePositionVector.x_, mousePositionVector.y_);
  }
}

void Player::RotateToMousePositionInLocalCoordinateSystem(
    float x, float y, Dimensions2D* window_dimensions) {
  if (x <= window_dimensions->width && y <= window_dimensions->height) {
    float current_x = x;
    float current_y = y;

    WindowPositionToCartesianPosition(current_x, current_y, window_dimensions);

    Vector2D current_mouse_position = Vector2D(current_x, current_y);

    Vector2D mouse_direction_in_local_coordination_system =
        Vector2D::CreateUnitVectorFromBoundVector(current_mouse_position,
                                                         position);

    float angle_between_current_and_mouse = Vector2D::AngleBetweenVectors(
        direction_, mouse_direction_in_local_coordination_system);

    RotateAllVerticesOverAnAngle(angle_between_current_and_mouse);
    Vector2D::RotateVectorOverTheAngle(&direction_,
                                              angle_between_current_and_mouse);
  }
}

void Player::set_direction(float x, float y) {
  direction_.x_ = x;
  direction_.y_ = y;
}

void Player::Generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x_ = position.x_ + local_vertices_[i].x_;
    world_vertices_[i].y_ = position.y_ + local_vertices_[i].y_;
  }
}

void Player::GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                            int number_of_vertices) {}

void Player::RegeneratePolygon() { Generate(); }

void Player::RotateAllVerticesOverAnAngle(float angle) {
  for (int i = 0; i < number_of_vertices_; i++) {
    Vector2D::RotateVectorOverTheAngle(&local_vertices_[i], angle);
  }
}

void Player::set_input(YasInOut::Input* input) {
  this->input_ = input;
}

void Player::set_input(YasInOut::MousePositionChangeInformation* mouse) {
  this->mouse_ = mouse;
}
