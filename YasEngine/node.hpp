#ifndef SPAWNERSQUADTREE_HPP
#define SPAWNERSQUADTREE_HPP

#include <vector>

#include "Spawner.hpp"
#include "vector_2d.hpp"

class Node {
 public:
  Node(Vector2D<int>* position, int size, Node* parent);
  Vector2D<int>* position_;
  int size_;
  Node* parent_node_;
  Node* child_nodes_[4];
  Spawner* spawner_;
  bool is_player_on_this_quad_;
  void CreateSpanwer(const std::vector<int>& spawner_position_number);

  static void AddNodes(Node& parent_node) {
    short factor_x = 1;
    short factor_y = 1;

    for (int i = 0; i < 4; i++) {
      switch (i) {
        case 0:
          factor_x = -1;
          factor_y = 1;
          ;
          break;
        case 1:
          factor_x = 1;
          factor_y = 1;
          ;
          break;
        case 2:
          factor_x = -1;
          factor_y = -1;
          ;
          break;
        case 3:
          factor_x = 1;
          factor_y = -1;
          ;
          break;
      }

      int child_node_size = static_cast<int>(parent_node.size_ * 0.5);
      int child_node_position_x = static_cast<int>(parent_node.position_->x_ +
                                            (factor_x * (child_node_size * 0.5)));
      int child_node_position_y = static_cast<int>(parent_node.position_->y_ +
                                            (factor_y * (child_node_size * 0.5)));
      Vector2D<int>* child_node_position =
          new Vector2D<int>(child_node_position_x, child_node_position_y);
      parent_node.child_nodes_[i] =
          new Node(child_node_position, child_node_size, &parent_node);

    }  // end for
  }

  static std::vector<Vector2D<int>*> GenerateTestPositions() {
    short factor_x = 1;
    short factor_y = 1;

    std::vector<Vector2D<int>*> positions;

    int zero_level_quad_size = 800;
    int zero_level_quad_pos_x = -400;
    int zero_level_quad_pos_y = 0;

    for (int j = 0; j < 4; j++) {
      switch (j) {
        case 0:
          factor_x = -1;
          factor_y = 1;
          ;
          break;
        case 1:
          factor_x = 1;
          factor_y = 1;
          ;
          break;
        case 2:
          factor_x = -1;
          factor_y = -1;
          ;
          break;
        case 3:
          factor_x = 1;
          factor_y = -1;
          ;
          break;
      }
      int first_level_quad_size = static_cast<int>(zero_level_quad_size * 0.5);
      int first_level_quad_position_x = static_cast<int>(
          zero_level_quad_pos_x + (factor_x * (first_level_quad_size * 0.5)));
      int first_level_quad_position_y = static_cast<int>(
          zero_level_quad_pos_y + (factor_y * (first_level_quad_size * 0.5)));

      positions.push_back(
          new Vector2D<int>(first_level_quad_position_x, first_level_quad_position_y));

      for (int i = 0; i < 4; i++) {
        switch (i) {
          case 0:
            factor_x = -1;
            factor_y = 1;
            ;
            break;
          case 1:
            factor_x = 1;
            factor_y = 1;
            ;
            break;
          case 2:
            factor_x = -1;
            factor_y = -1;
            ;
            break;
          case 3:
            factor_x = 1;
            factor_y = -1;
            ;
            break;
        }

        int second_level_quadsize = static_cast<int>(first_level_quad_size * 0.5);
        int second_level_quad_position_x = static_cast<int>(
            first_level_quad_position_x + (factor_x * (0.5 * second_level_quadsize)));
        int second_level_quad_position_y = static_cast<int>(
            first_level_quad_position_y + (factor_y * (0.5 * second_level_quadsize)));
        positions.push_back(new Vector2D<int>(second_level_quad_position_x,
                                              second_level_quad_position_y));
      }  // end for
    }
    return positions;
  }
};

#endif  // SPAWNERSQUADTREE_HPP
