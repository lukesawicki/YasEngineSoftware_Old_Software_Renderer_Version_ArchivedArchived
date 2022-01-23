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
	int circleX;
	int circleY;
	Vector2D<int> circlePixelPosition;
	for (int i = 0; i < 360; i++)
	{
		circleX = static_cast<int>(position.x + radius * cos(i));
		circleY = static_cast<int>(position.y + radius * sin(i));

		circlePixelPosition.x = circleX;
		circlePixelPosition.y = circleY;

		pixelsTable.drawPoint(&circlePixelPosition, drawingColor);
	}
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
