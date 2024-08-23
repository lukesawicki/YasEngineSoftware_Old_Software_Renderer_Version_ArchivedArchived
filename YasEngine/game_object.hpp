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

  virtual void generate() = 0;
  virtual void generateRegularPolygonVertices(float circumscribedCircleRadius,
                                              int numberOfVertices) = 0;
  virtual void regeneratePolygon() = 0;

  void setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    moveCollider();
  }

  void setX(float x) {
    position.x = x;
    moveCollider();
  }

  void setY(float y) {
    position.y = y;
    moveCollider();
  }

  virtual Vector2D<float> getPosition() { return position; }

  virtual int getColliderLeftSide() {
    return static_cast<int>(position.x - collider_.radius);
  }

  virtual int getColliderRightSide() {
    return static_cast<int>(position.x + collider_.radius);
  }

  virtual int getColliderTopSide() {
    return static_cast<int>(position.y + collider_.radius);
  }

  virtual int getColliderBottomSide() {
    return static_cast<int>(position.y - collider_.radius);
  }

  virtual void setPosition(const Vector2D<float>& position) {
    this->position.x = position.x;
    this->position.y = position.y;
    moveCollider();
  }

  virtual void move(float deltaTime) = 0;

  virtual void moveCollider() {
    collider_.x = position.x;
    collider_.y = position.y;
  }

  virtual void setColor(const Vector4D<Uint8>& color) {
    this->color_.x = color.x;
    this->color_.y = color.y;
    this->color_.z = color.z;
    this->color_.w = color.w;
  }

 protected:
  Vector2D<float> position;
};

#endif
