#include "Circle.hpp"

#include "yas_engine.hpp"
#include "yas_graphics_library.hpp"

Circle::Circle(float radius, float x, float y) {
  is_direction_switched_ = false;
  speed_ = 200;
  this->position.x_ = x;
  this->position.y_ = y;
  GenerateRegularPolygonVertices(radius, 64);
}

Circle::~Circle() { delete[] world_vertices_; }

void Circle::Move(float deltaTime) {
  position.x_ = position.x_ + static_cast<float>(deltaTime) * speed_;
  if (position.x_ < circumscribed_circle_radius_ && !is_direction_switched_) {
    speed_ = speed_ * -1;
    position.x_ = circumscribed_circle_radius_;
  }

  if (position.x_ > 512 - circumscribed_circle_radius_) {
    speed_ = speed_ * -1;
    position.x_ = 512 - circumscribed_circle_radius_;
  }

  RegeneratePolygon();
}

void Circle::Generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x_ = position.x_ + local_vertices_[i].x_;
    world_vertices_[i].y_ = position.y_ + local_vertices_[i].y_;
  }
}

void Circle::GenerateRegularPolygonVertices(float circumscribedCircleRadius,
                                            int numberOfVertices) {
  this->circumscribed_circle_radius_ = circumscribedCircleRadius;
  this->number_of_vertices_ = numberOfVertices;
  this->world_vertices_ = new Vector2D<float>[numberOfVertices];
  this->local_vertices_ = new Vector2D<float>[numberOfVertices];

  angle_for_generate_in_isosceles_polygons_ = start_angle_;
  step_angle_ = 360.0F / numberOfVertices;
  for (int i = 0; i < numberOfVertices; i++) {
    local_vertices_[i].x_ =
        0.0F + static_cast<int>(circumscribedCircleRadius *
                                cos(angle_for_generate_in_isosceles_polygons_ *
                                    (kPi / 180.0F)));
    local_vertices_[i].y_ =
        0.0F + static_cast<int>(circumscribedCircleRadius *
                                sin(angle_for_generate_in_isosceles_polygons_ *
                                    (kPi / 180.0F)));
    angle_for_generate_in_isosceles_polygons_ += step_angle_;
  }
  Generate();
}

void Circle::RegeneratePolygon() { Generate(); }
