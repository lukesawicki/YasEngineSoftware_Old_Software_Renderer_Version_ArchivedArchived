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
  Node* parentNode_;
  Node* child_nodes_[4];
  Spawner* spawner_;
  bool is_player_on_this_quad_;
  void CreateSpanwer(const std::vector<int>& spawner_position_number);

  static void AddNodes(Node& parent_node) {
    short factorX = 1;
    short factorY = 1;

    Vector2D<int>* childNodePosition;

    int childNodePositionX = 0;
    int childNodePositionY = 0;
    for (int i = 0; i < 4; i++) {
      switch (i) {
        case 0:
          factorX = -1;
          factorY = 1;
          ;
          break;
        case 1:
          factorX = 1;
          factorY = 1;
          ;
          break;
        case 2:
          factorX = -1;
          factorY = -1;
          ;
          break;
        case 3:
          factorX = 1;
          factorY = -1;
          ;
          break;
      }

      int childNodeSize = static_cast<int>(parent_node.size_ * 0.5);
      childNodePositionX = static_cast<int>(parent_node.position_->x_ +
                                            (factorX * (childNodeSize * 0.5)));
      childNodePositionY = static_cast<int>(parent_node.position_->y_ +
                                            (factorY * (childNodeSize * 0.5)));
      childNodePosition =
          new Vector2D<int>(childNodePositionX, childNodePositionY);
      parent_node.child_nodes_[i] =
          new Node(childNodePosition, childNodeSize, &parent_node);

    }  // end for
  }

  static std::vector<Vector2D<int>*> GenerateTestPositions() {
    short factorX = 1;
    short factorY = 1;

    std::vector<Vector2D<int>*> positions;

    int zeroLevelQuadSize = 800;
    int zeroLevelQuadPosX = -400;
    int zeroLevelQuadPosY = 0;

    int firstLevelQuadPositionX = 0;
    int firstLevelQuadPositionY = 0;
    int firstLevelQuadSize = 0;

    int secondLevelQuadPositionX = 0;
    int secondLevelQuadPositionY = 0;
    int secondLevelQuadsize = 0;

    for (int j = 0; j < 4; j++) {
      switch (j) {
        case 0:
          factorX = -1;
          factorY = 1;
          ;
          break;
        case 1:
          factorX = 1;
          factorY = 1;
          ;
          break;
        case 2:
          factorX = -1;
          factorY = -1;
          ;
          break;
        case 3:
          factorX = 1;
          factorY = -1;
          ;
          break;
      }
      firstLevelQuadSize = static_cast<int>(zeroLevelQuadSize * 0.5);
      firstLevelQuadPositionX = static_cast<int>(
          zeroLevelQuadPosX + (factorX * (firstLevelQuadSize * 0.5)));
      firstLevelQuadPositionY = static_cast<int>(
          zeroLevelQuadPosY + (factorY * (firstLevelQuadSize * 0.5)));

      positions.push_back(
          new Vector2D<int>(firstLevelQuadPositionX, firstLevelQuadPositionY));

      for (int i = 0; i < 4; i++) {
        switch (i) {
          case 0:
            factorX = -1;
            factorY = 1;
            ;
            break;
          case 1:
            factorX = 1;
            factorY = 1;
            ;
            break;
          case 2:
            factorX = -1;
            factorY = -1;
            ;
            break;
          case 3:
            factorX = 1;
            factorY = -1;
            ;
            break;
        }

        secondLevelQuadsize = static_cast<int>(firstLevelQuadSize * 0.5);
        secondLevelQuadPositionX = static_cast<int>(
            firstLevelQuadPositionX + (factorX * (0.5 * secondLevelQuadsize)));
        secondLevelQuadPositionY = static_cast<int>(
            firstLevelQuadPositionY + (factorY * (0.5 * secondLevelQuadsize)));
        positions.push_back(new Vector2D<int>(secondLevelQuadPositionX,
                                              secondLevelQuadPositionY));
      }  // end for
    }
    return positions;
  }
};

#endif  // SPAWNERSQUADTREE_HPP
