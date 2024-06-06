#include "Collectible.hpp"
#include "YasGraphicsLibrary.hpp"
#include<cstdlib>

Collectible::Collectible(float radius, float x, float y, int numberOfVertices)
{
	isAlive = true;
	iAm = GameObject::COLLECTIBLE;
	collider.radius = radius;
	speed = 20;
	this->position.x = x;
	this->position.y = y;
	this->collider.x = x;
	this->collider.y = y;
	float angle = static_cast<float>(Randomizer::drawNumberClosedInterval(0, 180));
	direction.x = 1;
	direction.y = 0;
	angle = angle * (PI / 180.0F);
	Vector2D<float>::rotateVectorOverTheAngle(&direction, angle);
	velocity.x = speed * direction.x;
	velocity.y = speed * direction.y;
	setRandomColor();
	generateRegularPolygonVertices(radius, numberOfVertices);
}

Collectible::~Collectible()
{
	delete[] worldVertices;
}

void Collectible::generate()
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + localVertices[i].x;
		worldVertices[i].y = position.y + localVertices[i].y;
	}
}

void Collectible::generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->worldVertices = new Vector2D<float>[numberOfVertices];
	this->localVertices = new Vector2D<float>[numberOfVertices];

	angleForGenerateInIsoscelesPolygons = startAngle;
	stepAngle = 360.0F / numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++)
	{
		localVertices[i].x = 0.0F + static_cast<int>(circumscribedCircleRadius * cos(angleForGenerateInIsoscelesPolygons * (PI / 180.0F)));
		localVertices[i].y = 0.0F + static_cast<int>(circumscribedCircleRadius * sin(angleForGenerateInIsoscelesPolygons * (PI / 180.0F)));
		angleForGenerateInIsoscelesPolygons += stepAngle;
	}
	generate();
}

void Collectible::regeneratePolygon()
{
	generate();
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
	position.x = position.x + deltaTime * velocity.x;
	position.y = position.y + deltaTime * velocity.y;
	moveCollider();
	regeneratePolygon();
}

void Collectible::setColor(const Vector4D<Uint8>& color)
{
	GameObject::setColor(color);
}

void Collectible::setRandomColor()
{
	int col = Randomizer::drawNumberClosedInterval(0, 8);
	switch(col)
	{
	case 0:
		setColor(RED);
		break;
	case 1:
		setColor(GREEN);
		break;
	case 2:
		setColor(BLUE);
		break;
	case 3:
		setColor(WHITE);
		break;
	case 4:
		setColor(YELLOW);
	case 5:
		setColor(LIGHT_BLUE);
		break;
	case 6:
		setColor(POLYGON);
		break;
	case 7:
		setColor(XPORTAL);
		break;
	case 8:
		setColor(PURPLE);
		break;
	default:
		setColor(BLUE);
		break;
	}
}
