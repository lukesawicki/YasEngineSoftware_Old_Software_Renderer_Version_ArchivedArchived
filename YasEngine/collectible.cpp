#include "collectible.hpp"

#include <cstdlib>

#include "randomizer.hpp"
#include "yas_graphics_library.hpp"

Collectible::Collectible(float radius, float x, float y, int number_of_vertices) {
  is_alive_ = true;
  i_am_ = GameObject::kCollectible;
  collider_.radius_ = radius;
  speed_ = 20;
  this->position.x_ = x;
  this->position.y_ = y;
  this->collider_.x_ = x;
  this->collider_.y_ = y;
  float angle =
      static_cast<float>(Randomizer::DrawNumberClosedInterval(0, 180));
  direction_.x_ = 1;
  direction_.y_ = 0;
  angle = angle * (kPi / 180.0F);
  Vector2D<float>::RotateVectorOverTheAngle(&direction_, angle);
  velocity_.x_ = speed_ * direction_.x_;
  velocity_.y_ = speed_ * direction_.y_;
  SetRandomColor();
  GenerateRegularPolygonVertices(radius, number_of_vertices);
}

Collectible::~Collectible() { delete[] world_vertices_; }

void Collectible::Generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x_ = position.x_ + local_vertices_[i].x_;
    world_vertices_[i].y_ = position.y_ + local_vertices_[i].y_;
  }
}

void Collectible::GenerateRegularPolygonVertices(
    float circumscribed_circle_radius, int number_of_vertices) {
  this->circumscribed_circle_radius_ = circumscribed_circle_radius;
  this->number_of_vertices_ = number_of_vertices;
  this->world_vertices_ = new Vector2D<float>[number_of_vertices];
  this->local_vertices_ = new Vector2D<float>[number_of_vertices];

  angle_for_generate_in_isosceles_polygons_ = start_angle_;
  step_angle_ = 360.0F / number_of_vertices;
  for (int i = 0; i < number_of_vertices; i++) {
    local_vertices_[i].x_ =
        0.0F + static_cast<int>(circumscribed_circle_radius *
                                cos(angle_for_generate_in_isosceles_polygons_ *
                                    (kPi / 180.0F)));
    local_vertices_[i].y_ =
        0.0F + static_cast<int>(circumscribed_circle_radius *
                                sin(angle_for_generate_in_isosceles_polygons_ *
                                    (kPi / 180.0F)));
    angle_for_generate_in_isosceles_polygons_ += step_angle_;
  }
  Generate();
}

void Collectible::RegeneratePolygon() { Generate(); }

void Collectible::set_position(float x, float y) {
  GameObject::set_position(x, y);
}

void Collectible::set_position(const Vector2D<float>& position) {
  GameObject::set_position(position);
}

void Collectible::Move(float delta_time) {
  position.x_ = position.x_ + delta_time * velocity_.x_;
  position.y_ = position.y_ + delta_time * velocity_.y_;
  MoveCollider();
  RegeneratePolygon();
}

void Collectible::set_color(const Vector4D<Uint8>& color) {
  GameObject::set_color(color);
}

void Collectible::SetRandomColor() {
  int col = Randomizer::DrawNumberClosedInterval(0, 8);
  switch (col) {
    case 0:
      set_color(kRed);
      break;
    case 1:
      set_color(kGreen);
      break;
    case 2:
      set_color(kBlue);
      break;
    case 3:
      set_color(kWhite);
      break;
    case 4:
      set_color(kYellow);
    case 5:
      set_color(kLightBlue);
      break;
    case 6:
      set_color(kPolygon);
      break;
    case 7:
      set_color(kXportal);
      break;
    case 8:
      set_color(kPurple);
      break;
    default:
      set_color(kBlue);
      break;
  }
}
