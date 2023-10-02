#include"Node.hpp"

Node::Node(Vector2D<int>* position, int size, Node* parent)
{
	this->position = position;
	this->size = size;
	this->parentNode = parent;
}

void Node::createSpanwer(const std::vector<int>& spawnerPositionNumber)
{
	this->childNodes[spawnerPositionNumber.at(0)]->childNodes[spawnerPositionNumber.at(1)]->spawner = new Spawner();

	this->childNodes[spawnerPositionNumber.at(0)]->childNodes[spawnerPositionNumber.at(1)]->spawner->position.x =
		this->childNodes[spawnerPositionNumber.at(0)]->childNodes[spawnerPositionNumber.at(1)]->position->x;
	this->childNodes[spawnerPositionNumber.at(0)]->childNodes[spawnerPositionNumber.at(1)]->spawner->position.y =
		this->childNodes[spawnerPositionNumber.at(0)]->childNodes[spawnerPositionNumber.at(1)]->position->y;
}

