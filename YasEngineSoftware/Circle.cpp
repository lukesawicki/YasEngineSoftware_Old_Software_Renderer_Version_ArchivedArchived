#include"Circle.hpp"

Circle::Circle(float radius, float x, float y)
{
	directionSwitched = false;
	speed = 200;
	YasVector2D<float> position(x, y);
	generateRegularPolygonVertices(position, radius, 64);
}

Circle::~Circle()
{
	delete[] worldVertices;
}

void Circle::move(float deltaTime)
{
	position.x = position.x + deltaTime * speed;
	if (position.x < circumscribedCircleRadius && !directionSwitched)
	{
		speed = speed * -1;
		position.x = circumscribedCircleRadius;
	}

	if (position.x > 512 - circumscribedCircleRadius)
	{
		speed = speed * -1;
		position.x = 512 - circumscribedCircleRadius;
	}
}

void Circle::generate()
{
	angle = startAngle;
	stepAngle = 360.0F / numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + static_cast<int>(circumscribedCircleRadius * cos(angle*(PI/180.0F)));
		worldVertices[i].y = position.y + static_cast<int>(circumscribedCircleRadius * sin(angle*(PI / 180.0F)));
		angle += stepAngle;
	}
}

void Circle::generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->position.x = position.x;
	this->position.y = position.y;
	this->worldVertices = new YasVector2D<float>[numberOfVertices];
	generate();
}

void Circle::regeneratePolygon()
{
	generate();
}
