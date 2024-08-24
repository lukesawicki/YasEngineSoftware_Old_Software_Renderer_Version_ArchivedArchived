#include "node.hpp"

Node::Node(Vector2D<int>* position, int size, Node* parent) {
  this->position_ = position;
  this->size_ = size;
  this->parentNode_ = parent;
}

void Node::CreateSpanwer(const std::vector<int>& spawner_position_number) {
  this->child_nodes_[spawner_position_number.at(0)]
      ->child_nodes_[spawner_position_number.at(1)]
      ->spawner_ = new Spawner();

  this->child_nodes_[spawner_position_number.at(0)]
      ->child_nodes_[spawner_position_number.at(1)]
      ->spawner_->position_.x_ = this->child_nodes_[spawner_position_number.at(0)]
                                     ->child_nodes_[spawner_position_number.at(1)]
                                     ->position_->x_;

  this->child_nodes_[spawner_position_number.at(0)]
      ->child_nodes_[spawner_position_number.at(1)]
      ->spawner_->position_.y_ = this->child_nodes_[spawner_position_number.at(0)]
                                     ->child_nodes_[spawner_position_number.at(1)]
                                     ->position_->y_;
}
