#include "Collider.hpp"

Collider::Collider() {
  this->radius_ = 0.0F;
  this->x_ = 0.0F;
  this->y_ = 0.0F;
}

Collider::Collider(float radius, float x, float y) {
  this->radius_ = radius;
  this->x_ = x;
  this->y_ = y;
}

bool Collider::IsCollision(const Collider& object_0, const Collider& object_1) {
  return (sqrt(pow(object_1.x_ - object_0.x_, 2.0) +
               pow(object_1.y_ - object_0.y_, 2.0))) <=
         (static_cast<double>(object_0.radius_) +
          static_cast<double>(object_1.radius_));
}

bool Collider::IsCollidingWithWall(const Collider& object_0,
                                   const Vector2D<int>& world_sizes) {
  return object_0.x_ - object_0.radius_ <
             -static_cast<float>(world_sizes.x_) * 0.5F ||  // LEFT
         object_0.x_ + object_0.radius_ >
             static_cast<float>(world_sizes.x_) * 0.5F ||  // RIGHT
         object_0.y_ + object_0.radius_ >
             static_cast<float>(world_sizes.y_) * 0.5F ||  // TOP
         object_0.y_ - object_0.radius_ <
             -static_cast<float>(world_sizes.y_) * 0.5F;  // BOTTOM
}

bool Collider::IsCollidingWithCustomWalls(const Collider& object_0,
                                          const Vector2D<int>& world_sizes) {
  return object_0.x_ - object_0.radius_ <
             -static_cast<float>(world_sizes.x_) * 0.5F ||  // LEFT
         object_0.x_ + object_0.radius_ >
             static_cast<float>(world_sizes.x_) * 0.0F ||  // RIGHT
         object_0.y_ + object_0.radius_ >
             static_cast<float>(world_sizes.y_) * 0.5F ||  // TOP
         object_0.y_ - object_0.radius_ <
             -static_cast<float>(world_sizes.y_) * 0.5F;  // BOTTOM
}
