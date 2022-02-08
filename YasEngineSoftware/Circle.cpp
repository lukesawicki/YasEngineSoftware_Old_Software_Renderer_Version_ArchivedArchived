#include"Circle.hpp"

YasGL::Circle::Circle(int radius, int x, int y)
{
	directionSwitched = false;
	speedFactor = 255;
	speed = 2 * speedFactor;
	Vector2D<int> position(x, y);
	generateRegularPolygonVertices(position, radius, 64);
}

YasGL::Circle::~Circle()
{
	delete[] worldVertices;
}

void YasGL::Circle::move(double deltaTime)
{
	position.x = static_cast<int>(position.x + deltaTime * speed);
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

void YasGL::Circle::generate()
{
	angle = startAngle;
	stepAngle = 360.0F / numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + static_cast<int>(circumscribedCircleRadius * cos(angle*(YasGL::PI/180.0F)));
		worldVertices[i].y = position.y + static_cast<int>(circumscribedCircleRadius * sin(angle*(YasGL::PI / 180.0F)));
		angle += stepAngle;
	}
}

void YasGL::Circle::generateRegularPolygonVertices(const Vector2D<int>& position, int circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->position.x = position.x;
	this->position.y = position.y;
	this->worldVertices = new Vector2D<int>[numberOfVertices];
	generate();
}

void YasGL::Circle::regeneratePolygon()
{
	generate();
}
