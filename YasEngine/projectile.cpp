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
  collider_.radius_ = radius;
  speed_ = 200;
  this->position.x_ = x;
  this->position.y_ = y;
  this->collider_.x_ = x;
  this->collider_.y_ = y;

  velocity_.x_ = speed_ * direction.x_;
  velocity_.y_ = speed_ * direction.y_;
  color_ = kYellow;
  GenerateRegularPolygonVertices(radius, 4);
  start_time_ = time_picker_.GetMiliseconds();
}

Projectile::~Projectile() {
  delete[] world_vertices_;
  delete[] local_vertices_;
}

void Projectile::Move(float delta_time) {
  if (time_picker_.GetMiliseconds() - start_time_ >= 2000) {
    this->is_alive_ = false;
  }

  position.x_ = position.x_ + delta_time * velocity_.x_;
  position.y_ = position.y_ + delta_time * velocity_.y_;
  MoveCollider();
  RegeneratePolygon();
}

void Projectile::Generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x_ = position.x_ + local_vertices_[i].x_;
    world_vertices_[i].y_ = position.y_ + local_vertices_[i].y_;
  }
}

void Projectile::GenerateRegularPolygonVertices(float circumscribed_circle_radius,
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

void Projectile::RegeneratePolygon() { Generate(); }
