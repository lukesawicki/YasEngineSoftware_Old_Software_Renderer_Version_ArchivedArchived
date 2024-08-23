#include "projectile.hpp"

#include "yas_graphics_library.hpp"

static Uint32 kill(Projectile* projectileToKill, Uint32 interval, void* param) {
  projectileToKill->is_alive_ = false;
  return 0;
}

Projectile::Projectile(float radius, float x, float y,
                       Vector2D<float> direction) {
  is_alive_ = true;
  i_am_ = WhoAmI::kProjectile;
  collider_.radius = radius;
  speed_ = 200;
  this->position.x = x;
  this->position.y = y;
  this->collider_.x = x;
  this->collider_.y = y;

  velocity_.x = speed_ * direction.x;
  velocity_.y = speed_ * direction.y;
  color_ = kYellow;
  generateRegularPolygonVertices(radius, 4);
  start_time_ = time_picker_.getMiliseconds();
}

Projectile::~Projectile() {
  delete[] world_vertices_;
  delete[] local_vertices_;
}

void Projectile::Move(float deltaTime) {
  if (time_picker_.getMiliseconds() - start_time_ >= 2000) {
    this->is_alive_ = false;
  }

  position.x = position.x + deltaTime * velocity_.x;
  position.y = position.y + deltaTime * velocity_.y;
  moveCollider();
  regeneratePolygon();
}

void Projectile::generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x = position.x + local_vertices_[i].x;
    world_vertices_[i].y = position.y + local_vertices_[i].y;
  }
}

void Projectile::generateRegularPolygonVertices(float circumscribedCircleRadius,
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

void Projectile::regeneratePolygon() { generate(); }
