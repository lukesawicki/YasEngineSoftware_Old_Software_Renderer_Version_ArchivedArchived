#include "player.hpp"
#include "yas_engine.hpp"
#include "yas_graphics_library.hpp"

Player::Player(float x, float y) {
  collider_.x = x;
  collider_.y = y;
  collider_.radius = 20;
  i_am_ = WhoAmI::kProtagonist;
  position.x = x;
  position.y = y;

  direction_.x = 1;
  direction_.y = 0;

  speed_ = 200;
  rotation_speed_ = 5;

  number_of_vertices_ = 17;

  world_vertices_ = new Vector2D<float>[number_of_vertices_];
  local_vertices_ = new Vector2D<float>[number_of_vertices_];

  local_vertices_[0].x = -12;
  local_vertices_[0].y = -11;

  local_vertices_[1].x = -2;
  local_vertices_[1].y = -11;

  local_vertices_[2].x = 8;
  local_vertices_[2].y = -9;

  local_vertices_[3].x = -2;
  local_vertices_[3].y = -7;

  local_vertices_[4].x = -2;
  local_vertices_[4].y = -3;

  local_vertices_[5].x = 12;
  local_vertices_[5].y = 0;

  local_vertices_[6].x = -2;
  local_vertices_[6].y = 3;

  local_vertices_[7].x = -2;
  local_vertices_[7].y = 7;

  local_vertices_[8].x = 8;
  local_vertices_[8].y = 9;

  local_vertices_[9].x = -2;
  local_vertices_[9].y = 11;

  local_vertices_[10].x = -12;
  local_vertices_[10].y = 11;

  local_vertices_[11].x = -8;
  local_vertices_[11].y = 7;

  local_vertices_[12].x = -12;
  local_vertices_[12].y = 3;

  local_vertices_[13].x = -8;
  local_vertices_[13].y = 3;

  local_vertices_[14].x = -8;
  local_vertices_[14].y = -3;

  local_vertices_[15].x = -12;
  local_vertices_[15].y = -3;

  local_vertices_[16].x = -8;
  local_vertices_[16].y = -7;

  generate();
}

Player::~Player() {
  delete[] world_vertices_;
  delete[] local_vertices_;
  // delete input_; // It will be deleted in YasEngine
  // delete mouse_; // It will be deleted in YasEngine
}

void Player::move(float deltaTime) {
  // LEFT
  if (input_->left && !input_->right) {
    position.x = position.x + deltaTime * (-speed_);
  }

  // RIGHT
  if (input_->right && !input_->left) {
    position.x = position.x + deltaTime * speed_;
  }

  // UP
  if (input_->up && !input_->down) {
    position.y = position.y + deltaTime * speed_;
  }

  // DOWN
  if (input_->down && !input_->up) {
    position.y = position.y + deltaTime * (-speed_);
  }

  moveCollider();

  // SPACE
  if (input_->shoot || mouse_->leftMouseButton) {
    is_shooting_ = true;
  }
  regeneratePolygon();
}

void Player::rotate(float deltaTime) {
  if (input_->rotateCounterClockwise) {
    direction_mouse_angle_ = direction_mouse_angle_ * 3.141592F / 180.0F;
    direction_mouse_angle_ = deltaTime * rotation_speed_;
    player_current_direction_angle_ =
        player_current_direction_angle_ + direction_mouse_angle_;
    if (player_current_direction_angle_ >= 6.28319F) {
      player_current_direction_angle_ =
          player_current_direction_angle_ - 6.28319F;
    }
    rotateAllVerticesOverAnAngle(direction_mouse_angle_);
    generate();
  }
}

void Player::rotateToMousePosition(float x, float y,
                                   Vector2D<int>* windowDimensions) {
  if (x <= windowDimensions->x && y <= windowDimensions->y) {
    float currentX = x;
    float currentY = y;

    windowPositionToCartesianPosition(currentX, currentY, windowDimensions);

    Vector2D<float> mousePositionVector(static_cast<float>(currentX),
                                        static_cast<float>(currentY));
    // Vector2D<float>::normalizedVector(mousePositionVector);

    float angleBetweenCurrentAndMouse =
        Vector2D<float>::angleBetweenVectors(direction_, mousePositionVector);
    rotateAllVerticesOverAnAngle(angleBetweenCurrentAndMouse);
    setDirection(mousePositionVector.x, mousePositionVector.y);
  }
}

void Player::rotateToMousePositionInLocalCoordinateSystem(
    float x, float y, Vector2D<int>* windowDimensions) {
  if (x <= windowDimensions->x && y <= windowDimensions->y) {
    float currentX = x;
    float currentY = y;

    windowPositionToCartesianPosition(currentX, currentY, windowDimensions);

    Vector2D<float> currentMousePosition = Vector2D<float>(currentX, currentY);

    Vector2D<float> mouseDirectionInLocalCoordynationSystem =
        Vector2D<float>::createUnitVectorFromBoundVector(currentMousePosition,
                                                         position);

    float angleBetweenCurrentAndMouse = Vector2D<float>::angleBetweenVectors(
        direction_, mouseDirectionInLocalCoordynationSystem);

    rotateAllVerticesOverAnAngle(angleBetweenCurrentAndMouse);
    Vector2D<float>::rotateVectorOverTheAngle(&direction_,
                                              angleBetweenCurrentAndMouse);
  }
}

void Player::setDirection(float x, float y) {
  direction_.x = x;
  direction_.y = y;
}

void Player::generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x = position.x + local_vertices_[i].x;
    world_vertices_[i].y = position.y + local_vertices_[i].y;
  }
}

void Player::generateRegularPolygonVertices(float circumscribedCircleRadius,
                                            int numberOfVertices) {}

void Player::regeneratePolygon() { generate(); }

void Player::rotateAllVerticesOverAnAngle(float angle) {
  for (int i = 0; i < number_of_vertices_; i++) {
    Vector2D<float>::rotateVectorOverTheAngle(&local_vertices_[i], angle);
  }
}

void Player::setInput(YasInOut::Input* input) { this->input_ = input; }

void Player::setInput(YasInOut::MousePositionChangeInformation* mouse) {
  this->mouse_ = mouse;
}

Projectile* Player::shoot() {
  if (is_shooting_) {
    is_shooting_ = false;
    float projectileX = position.x + direction_.x * projectile_position_shift_;
    float projectileY = position.y + direction_.y * projectile_position_shift_;
    return new Projectile(8, projectileX, projectileY, direction_);
  } else {
    return nullptr;
  }
}
