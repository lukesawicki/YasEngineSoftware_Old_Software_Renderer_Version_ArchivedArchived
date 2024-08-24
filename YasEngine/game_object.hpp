#ifndef game_object_hpp
#define game_object_hpp
#include <SDL.h>

#include "collider.hpp"
#include "vector_2d.hpp"
#include "vector_4d.hpp"

class GameObject {
 public:
  enum WhoAmI {
    kDefaultValue,
    kProtagonist,
    kProjectile,
    kCollectible,
    kGuiElement
  };

  WhoAmI i_am_;
  bool is_alive_ = true;
  Collider collider_;
  Vector2D<float>* local_vertices_ = nullptr;
  Vector2D<float>* world_vertices_ = nullptr;
  Vector2D<float> vector_zero_;
  Vector2D<float> direction_;
  Vector4D<Uint8> color_;
  int number_of_vertices_;
  float rotation_speed_;
  float circumscribed_circle_radius_;
  float angle_for_generate_in_isosceles_polygons_;
  float start_angle_ = 0.0F;
  float step_angle_;
  float direction_mouse_angle_ = 0;
  float speed_ = 0.0F;

  Vector2D<float> velocity_;

  virtual void Generate() = 0;
  virtual void GenerateRegularPolygonVertices(float circumscribedCircleRadius,
                                              int numberOfVertices) = 0;
  virtual void RegeneratePolygon() = 0;

  void setPosition(float x, float y) {
    position.x_ = x;
    position.y_ = y;
    moveCollider();
  }

  void setX(float x) {
    position.x_ = x;
    moveCollider();
  }

  void setY(float y) {
    position.y_ = y;
    moveCollider();
  }

  virtual Vector2D<float> getPosition() { return position; }

  virtual int getColliderLeftSide() {
    return static_cast<int>(position.x_ - collider_.radius_);
  }

  virtual int getColliderRightSide() {
    return static_cast<int>(position.x_ + collider_.radius_);
  }

  virtual int getColliderTopSide() {
    return static_cast<int>(position.y_ + collider_.radius_);
  }

  virtual int getColliderBottomSide() {
    return static_cast<int>(position.y_ - collider_.radius_);
  }

  virtual void set_position(const Vector2D<float>& position) {
    this->position.x_ = position.x_;
    this->position.y_ = position.y_;
    moveCollider();
  }

  virtual void Move(float deltaTime) = 0;

  virtual void moveCollider() {
    collider_.x_ = position.x_;
    collider_.y_ = position.y_;
  }

  virtual void set_color(const Vector4D<Uint8>& color) {
    this->color_.x_ = color.x_;
    this->color_.y_ = color.y_;
    this->color_.z_ = color.z_;
    this->color_.w_ = color.w_;
  }

 protected:
  Vector2D<float> position;
};

#endif
