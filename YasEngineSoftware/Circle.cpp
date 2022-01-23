#include"Circle.hpp"

Circle::Circle(int pointsNumber, int radius, int x, int y)
{
	position.x = x;
	position.y = y;
	points = new int[pointsNumber];
	this->radius = radius;
}

void Circle::draw(const Vector4D<uint8_t>& drawingColor, PixelsTable& pixelsTable)
{
	YasGL::drawCircle(&position, radius, pixelsTable, drawingColor);
}

void Circle::move(double deltaTime)
{
	position.x = static_cast<int>(position.x + deltaTime * speed);
	if (position.x < radius && !directionSwitched)
	{
		speed = speed * -1;
		position.x = radius;
	}

	if (position.x > 512 - radius)
	{
		speed = speed * -1;
		position.x = 512 - radius;
	}
}
