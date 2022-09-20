#include "Collectible.hpp"

Collectible::Collectible()
{
}

Collectible::~Collectible()
{
}

void Collectible::generate()
{
}

void Collectible::generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices)
{
}

void Collectible::regeneratePolygon()
{
}

void Collectible::setPosition(float x, float y)
{
	GameObject::setPosition(x, y);
}

void Collectible::setPosition(const Vector2D<float>& position)
{
	GameObject::setPosition(position);
}

void Collectible::move(float deltaTime)
{
}

void Collectible::setColor(const Vector4D<Uint8>& color)
{
	GameObject::setColor(color);
}