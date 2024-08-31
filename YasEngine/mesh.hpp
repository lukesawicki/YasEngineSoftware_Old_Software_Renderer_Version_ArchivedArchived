#ifndef MESH_HPP
#define MESH_HPP

#include<vector>
#include"point_3d.hpp"

template <typename Type>
class Mesh {
 public:
  std::vector<Point3d<Type>> points_model_;
  Vector4D<Type> model_position_;
  std::vector<Point3d<Type>> points_wold_;
  Vector4D<Type> world_position_;

  Mesh(const std::vector<Point3d<Type>>& points_model, const Vector4D<Type>& model_position, const Vector4D<Type>& world_position)
    : points_model_(points_model),
      model_position_(model_position),
      world_position_(world_position) {
  }
};

#endif
