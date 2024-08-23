#include "Circle.hpp"

#include "yas_engine.hpp"
#include "yas_graphics_library.hpp"

Circle::Circle(float radius, float x, float y) {
  directionSwitched = false;
  speed_ = 200;
  this->position.x = x;
  this->position.y = y;
  generateRegularPolygonVertices(radius, 64);
}

Circle::~Circle() { delete[] world_vertices_; }

void Circle::Move(float deltaTime) {
  position.x = position.x + static_cast<float>(deltaTime) * speed_;
  if (position.x < circumscribed_circle_radius_ && !directionSwitched) {
    speed_ = speed_ * -1;
    position.x = circumscribed_circle_radius_;
  }

  if (position.x > 512 - circumscribed_circle_radius_) {
    speed_ = speed_ * -1;
    position.x = 512 - circumscribed_circle_radius_;
  }

  regeneratePolygon();
}

void Circle::generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x = position.x + local_vertices_[i].x;
    world_vertices_[i].y = position.y + local_vertices_[i].y;
  }
}

void Circle::generateRegularPolygonVertices(float circumscribedCircleRadius,
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

void Circle::regeneratePolygon() { generate(); }
