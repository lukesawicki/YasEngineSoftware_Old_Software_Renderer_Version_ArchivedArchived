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
}

void Circle::generate()
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + localVertices[i].x;
		worldVertices[i].y = position.y + localVertices[i].y;
	}
}

void Circle::generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->position.x = position.x;
	this->position.y = position.y;
	this->worldVertices = new YasVector2D<float>[numberOfVertices];
	this->localVertices = new YasVector2D<float>[numberOfVertices];

	angleForGenerateInisoscelesPolygons = startAngle;
	stepAngle = 360.0F / numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++)
	{
		localVertices[i].x = 0.0F + static_cast<int>(circumscribedCircleRadius * cos(angleForGenerateInisoscelesPolygons * (PI / 180.0F)));
		localVertices[i].y = 0.0F + static_cast<int>(circumscribedCircleRadius * sin(angleForGenerateInisoscelesPolygons * (PI / 180.0F)));
		angleForGenerateInisoscelesPolygons += stepAngle;
	}

	generate();
}

void Circle::regeneratePolygon()
{
	generate();
}
