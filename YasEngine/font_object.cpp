#include "font_object.hpp"

#include <cstdlib>

#include "Randomizer.hpp"
#include "yas_graphics_library.hpp"

FontObject::FontObject() {}

void FontObject::initialize(float radius, float x, float y,
                            const Vector2D<float>& direction,
                            int numberOfVertices) {
  is_alive_ = true;
  i_am_ = GameObject::kGuiElement;
  collider_.radius = 17;
  speed_ = 200;
  this->direction_.x = direction.x;
  this->direction_.y = direction.y;
  this->position.x = x;
  this->position.y = y;
  this->collider_.x = x;
  this->collider_.y = y;
  start_angle_ = 90;
  velocity_.x = speed_ * direction.x;
  velocity_.y = speed_ * direction.y;
  setRandomColor();
}

FontObject::~FontObject() {
  delete[] world_vertices_;
  delete[] local_vertices_;
}

void FontObject::generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x = position.x + local_vertices_[i].x;
    world_vertices_[i].y = position.y + local_vertices_[i].y;
  }
}

void FontObject::generateRegularPolygonVertices(float circumscribedCircleRadius,
                                                int numberOfVertices) {
  this->circumscribed_circle_radius_ = circumscribedCircleRadius;
  this->number_of_vertices_ = numberOfVertices;
  this->world_vertices_ = new Vector2D<float>[numberOfVertices];
  this->local_vertices_ = new Vector2D<float>[numberOfVertices];

  angle_for_generate_in_isosceles_polygons_ = start_angle_;
  step_angle_ = 360.0F / numberOfVertices;
  for (int i = 0; i < numberOfVertices; i++) {
    local_vertices_[i].x =
        0.0F + static_cast<int>(circumscribedCircleRadius *
                                cos(angle_for_generate_in_isosceles_polygons_ *
                                    (kPi / 180.0F)));
    local_vertices_[i].y =
        0.0F + static_cast<int>(circumscribedCircleRadius *
                                sin(angle_for_generate_in_isosceles_polygons_ *
                                    (kPi / 180.0F)));
    angle_for_generate_in_isosceles_polygons_ += step_angle_;
  }
  generate();
}

void FontObject::regeneratePolygon() { generate(); }

void FontObject::setPosition(float x, float y) {
  GameObject::setPosition(x, y);
}

void FontObject::setPosition(const Vector2D<float>& position) {
  GameObject::setPosition(position);
}

void FontObject::Move(float deltaTime) {}

void FontObject::setColor(const Vector4D<Uint8>& color) {
  GameObject::setColor(color);
}

void FontObject::setRandomColor() {
  int col = Randomizer::drawNumberClosedInterval(1, 4);
  switch (col) {
    case 0:
      setColor(kRed);
      break;
    case 1:
      setColor(kGreen);
      break;
    case 2:
      setColor(kBlue);
      break;
    case 3:
      setColor(kWhite);
      break;
    case 4:
      setColor(kYellow);
      break;
    default:
      setColor(kBlue);
      break;
  }
}
