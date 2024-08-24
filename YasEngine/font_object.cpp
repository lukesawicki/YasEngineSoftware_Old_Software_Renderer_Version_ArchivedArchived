#include "font_object.hpp"

#include <cstdlib>

#include "Randomizer.hpp"
#include "yas_graphics_library.hpp"

FontObject::FontObject() {}

void FontObject::initialize(float radius, float x, float y,
                            const Vector2D<float>& direction,
                            int number_of_vertices) {
  is_alive_ = true;
  i_am_ = GameObject::kGuiElement;
  collider_.radius_ = 17;
  speed_ = 200;
  this->direction_.x_ = direction.x_;
  this->direction_.y_ = direction.y_;
  this->position.x_ = x;
  this->position.y_ = y;
  this->collider_.x_ = x;
  this->collider_.y_ = y;
  start_angle_ = 90;
  velocity_.x_ = speed_ * direction.x_;
  velocity_.y_ = speed_ * direction.y_;
  SetRandomColor();
}

FontObject::~FontObject() {
  delete[] world_vertices_;
  delete[] local_vertices_;
}

void FontObject::Generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x_ = position.x_ + local_vertices_[i].x_;
    world_vertices_[i].y_ = position.y_ + local_vertices_[i].y_;
  }
}

void FontObject::GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                                int number_of_vertices) {
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

void FontObject::RegeneratePolygon() { Generate(); }

void FontObject::set_position(float x, float y) {
  GameObject::set_position(x, y);
}

void FontObject::set_position(const Vector2D<float>& position) {
  GameObject::set_position(position);
}

void FontObject::Move(float delta_time) {}

void FontObject::set_color(const Vector4D<Uint8>& color) {
  GameObject::set_color(color);
}

void FontObject::SetRandomColor() {
  int col = Randomizer::DrawNumberClosedInterval(1, 4);
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
      break;
    default:
      set_color(kBlue);
      break;
  }
}
