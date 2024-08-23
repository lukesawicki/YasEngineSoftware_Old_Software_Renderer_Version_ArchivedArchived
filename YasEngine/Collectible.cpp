#include "collectible.hpp"

#include <cstdlib>

#include "randomizer.hpp"
#include "yas_graphics_library.hpp"

Collectible::Collectible(float radius, float x, float y, int numberOfVertices) {
  is_alive_ = true;
  i_am_ = GameObject::kCollectible;
  collider_.radius = radius;
  speed_ = 20;
  this->position.x = x;
  this->position.y = y;
  this->collider_.x = x;
  this->collider_.y = y;
  float angle =
      static_cast<float>(Randomizer::drawNumberClosedInterval(0, 180));
  direction_.x = 1;
  direction_.y = 0;
  angle = angle * (kPi / 180.0F);
  Vector2D<float>::rotateVectorOverTheAngle(&direction_, angle);
  velocity_.x = speed_ * direction_.x;
  velocity_.y = speed_ * direction_.y;
  setRandomColor();
  generateRegularPolygonVertices(radius, numberOfVertices);
}

Collectible::~Collectible() { delete[] world_vertices_; }

void Collectible::generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x = position.x + local_vertices_[i].x;
    world_vertices_[i].y = position.y + local_vertices_[i].y;
  }
}

void Collectible::generateRegularPolygonVertices(
    float circumscribedCircleRadius, int numberOfVertices) {
  this->circumscribed_circle_radius_ = circumscribedCircleRadius;
  this->number_of_vertices_ = numberOfVertices;
  this->world_vertices_ = new Vector2D<float>[numberOfVertices];
  this->local_vertices_ = new Vector2D<float>[numberOfVertices];

  angle_for_generate_in_isosceles_polygons_ = start_angle_;
  step_angle_ = 360.0F / numberOfVertices;
  for (int i = 0; i < numberOfVertices; i++) {
    local_vertices_[i].x =
        0.0F + static_cast<int>(
                   circumscribedCircleRadius *
                                cos(angle_for_generate_in_isosceles_polygons_ *
                                    (kPi / 180.0F)));
    local_vertices_[i].y =
        0.0F + static_cast<int>(
                   circumscribedCircleRadius *
                                sin(angle_for_generate_in_isosceles_polygons_ *
                                    (kPi / 180.0F)));
    angle_for_generate_in_isosceles_polygons_ += step_angle_;
  }
  generate();
}

void Collectible::regeneratePolygon() { generate(); }

void Collectible::setPosition(float x, float y) {
  GameObject::setPosition(x, y);
}

void Collectible::setPosition(const Vector2D<float>& position) {
  GameObject::setPosition(position);
}

void Collectible::Move(float deltaTime) {
  position.x = position.x + deltaTime * velocity_.x;
  position.y = position.y + deltaTime * velocity_.y;
  moveCollider();
  regeneratePolygon();
}

void Collectible::setColor(const Vector4D<Uint8>& color) {
  GameObject::setColor(color);
}

void Collectible::setRandomColor() {
  int col = Randomizer::drawNumberClosedInterval(0, 8);
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
    case 5:
      setColor(kLightBlue);
      break;
    case 6:
      setColor(kPolygon);
      break;
    case 7:
      setColor(kXportal);
      break;
    case 8:
      setColor(kPurple);
      break;
    default:
      setColor(kBlue);
      break;
  }
}
