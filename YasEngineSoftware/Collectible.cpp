#include "Collectible.hpp"
#include "YasGraphicsLibrary.hpp"
#include<cstdlib>     /* srand, rand */

Collectible::Collectible(float radius, float x, float y, Vector2D<float> direction)
{
	isAlive = true;
	iAm = GameObject::COLLECTIBLE;
	collider.radius = radius;
	speed = 200;
	Vector2D<float> position(x, y);
	velocity.x = speed * direction.x;
	velocity.y = speed * direction.y;
	setRandomColor();
	generateRegularPolygonVertices(position, radius, 4);
}

Collectible::~Collectible()
{
}

void Collectible::generate()
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + localVertices[i].x;
		worldVertices[i].y = position.y + localVertices[i].y;
	}
}

void Collectible::generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->position.x = position.x;
	this->position.y = position.y;
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
	srand(clock());
	int col = rand() % 5;
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
		break;
	default:
		setColor(BLUE);
		break;
	}
}

//v1 = rand() % 100;         // v1 in the range 0 to 99
//v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
//v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 

//RED
//GREEN
//BLUE
//WHITE
//YELLOW