#include"Collider.hpp"

Collider::Collider(float radius, float x, float y)
{
	this->radius = radius;
	this->x = x;
	this->y = y;
}
bool Collider::isInCollision(const Collider& object0, const Collider& object1)
{
	return (sqrt(pow(object1.x - object0.x, 2.0) + pow(object1.y - object0.y, 2.0))) <= (static_cast<double>(object1.radius) + static_cast<double>(object1.radius));
}
bool Collider::isCollidingWithWall(const Collider& object1)
{
	
}