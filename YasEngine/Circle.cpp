#include"Circle.hpp"
#include"YasEngine.hpp"

Circle::Circle(float radius, float x, float y)
{
	directionSwitched = false;
	speed = 200;
	this->position.x = x;
	this->position.y = y;
	generateRegularPolygonVertices(radius, 64);
}

Circle::~Circle()
{
	delete[] worldVertices;
}

void Circle::move(float deltaTime)
{
	position.x = position.x + static_cast<float>(deltaTime) * speed;
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

	regeneratePolygon();
}

void Circle::generate()
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + localVertices[i].x;
		worldVertices[i].y = position.y + localVertices[i].y;
	}
}

void Circle::generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices)
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

void Circle::regeneratePolygon()
{
	generate();
}
