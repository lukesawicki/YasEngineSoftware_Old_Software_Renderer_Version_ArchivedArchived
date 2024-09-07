#ifndef game_object_hpp
#define game_object_hpp

#include "collider.hpp"
#include "vector_2d.hpp"
#include "color.hpp"

class GameObject {
 public:
  enum WhoAmI {
    kDefaultValue,
    kPlayer,
    kProjectile,
    kCollectible,
    kGuiElement
  };

  WhoAmI i_am_;
  bool is_alive_ = true;
  Collider collider_;
  Vector2D* local_vertices_ = nullptr;
  Vector2D* world_vertices_ = nullptr;
  Vector2D vector_zero_;
  Vector2D direction_;
  Color color_;
  int number_of_vertices_;
  float rotation_speed_;
  float circumscribed_circle_radius_;
  float angle_for_generate_in_isosceles_polygons_;
  float start_angle_ = 0.0F;
  float step_angle_;
  float direction_mouse_angle_ = 0;
  float speed_ = 20.0F;

  Vector2D velocity_;

  virtual void Generate() = 0;
  virtual void GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                              int number_of_vertices) = 0;
  virtual void RegeneratePolygon() = 0;

  void set_position(float x, float y) {
    position.x_ = x;
    position.y_ = y;
    MoveCollider();
  }

  void set_x(float x) {
    position.x_ = x;
    MoveCollider();
  }

  void set_y(float y) {
    position.y_ = y;
    MoveCollider();
  }

  virtual Vector2D get_position() { return position; }

  virtual int GetColliderLeftSide() {
    return static_cast<int>(position.x_ - collider_.radius_);
  }

  virtual int GetColliderRightSide() {
    return static_cast<int>(position.x_ + collider_.radius_);
  }

  virtual int GetColliderTopSide() {
    return static_cast<int>(position.y_ + collider_.radius_);
  }

  virtual int GetColliderBottomSide() {
    return static_cast<int>(position.y_ - collider_.radius_);
  }

  virtual void set_position(const Vector2D& position) {
    this->position.x_ = position.x_;
    this->position.y_ = position.y_;
    MoveCollider();
  }

  virtual void Move(float delta_time) = 0;

  virtual void MoveCollider() {
    collider_.x_ = position.x_;
    collider_.y_ = position.y_;
  }

  virtual void set_color(const Color& color) {
    this->color_.red = color.red;
    this->color_.green = color.green;
    this->color_.blue = color.blue;
    this->color_.alpha = color.alpha;
  }

 protected:
  Vector2D position;
};

#endif
