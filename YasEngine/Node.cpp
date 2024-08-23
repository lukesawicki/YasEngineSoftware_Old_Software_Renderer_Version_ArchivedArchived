#include "node.hpp"

Node::Node(Vector2D<int>* position, int size, Node* parent) {
  this->position_ = position;
  this->size_ = size;
  this->parentNode_ = parent;
}

void Node::createSpanwer(const std::vector<int>& spawnerPositionNumber) {
  this->child_nodes_[spawnerPositionNumber.at(0)]
      ->child_nodes_[spawnerPositionNumber.at(1)]
      ->spawner_ = new Spawner();

  this->child_nodes_[spawnerPositionNumber.at(0)]
      ->child_nodes_[spawnerPositionNumber.at(1)]
      ->spawner_->position_.x = this->child_nodes_[spawnerPositionNumber.at(0)]
                                   ->child_nodes_[spawnerPositionNumber.at(1)]
                                   ->position_->x;

  this->child_nodes_[spawnerPositionNumber.at(0)]
      ->child_nodes_[spawnerPositionNumber.at(1)]
      ->spawner_->position_.y = this->child_nodes_[spawnerPositionNumber.at(0)]
                                   ->child_nodes_[spawnerPositionNumber.at(1)]
                                   ->position_->y;
}
