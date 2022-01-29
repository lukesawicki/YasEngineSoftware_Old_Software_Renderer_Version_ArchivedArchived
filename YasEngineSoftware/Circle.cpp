#include"Circle.hpp"

YasGL::Circle::Circle(int radius, int x, int y)
{
	Vector2D<int> position(x, y);
	generateRegularPolygonVertices(position, radius, 5);
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
	for (int i = 0; i < numberOfVertices; i++)
	{
		vertices[i].x = static_cast<int>(position.x + circumscribedCircleRadius * cos(i));
		vertices[i].y = static_cast<int>(position.y + circumscribedCircleRadius * sin(i));
		std::cout << "X: " << vertices[i].x << "Y: " << vertices[i].y << std::endl;
	}
}

void YasGL::Circle::generateRegularPolygonVertices(Vector2D<int>& position, int circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->position.x = position.x;
	this->position.y = position.y;
	vertices = new Vector2D<int>[numberOfVertices];
	generate();
}

//int circleX;
//int circleY;
//Vector2D<int> circlePixelPosition;
//for (int i = 0; i < 360; i++)
//{
//	circleX = static_cast<int>(position.x + radius * cos(i));
//	circleY = static_cast<int>(position.y + radius * sin(i));
//
//	circlePixelPosition.x = circleX;
//	circlePixelPosition.y = circleY;
//
//	pixelsTable.drawPoint(&circlePixelPosition, drawingColor);
//}