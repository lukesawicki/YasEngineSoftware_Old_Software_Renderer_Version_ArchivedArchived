#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include "vector_2d.hpp"

class Collider {
 public:
  float radius_ = 0.0F;
  float x_ = 0.0F;
  float y_ = 0.0F;
  Collider();
  Collider(float radius, float x, float y);
  bool is_in_collision_ = false;

  static bool IsCollision(const Collider& object_0, const Collider& object_1);
  static bool IsCollidingWithWall(const Collider& object_0,
                                  const Vector2D<int>& world_sizes);
  static bool IsCollidingWithCustomWalls(const Collider& object_0,
                                         const Vector2D<int>& world_sizes);

 private:
};

#endif
