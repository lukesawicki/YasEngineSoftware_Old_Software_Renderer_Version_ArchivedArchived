#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include"Shape.hpp"
#include"YasGraphicsLibrary.hpp"

class Circle: public Shape
{
	private:
		Vector2D<int> position;
		int radius = 0;
		bool directionSwitched = false;
		int speedFactor = 255;
		int speed = 2 * speedFactor;
	public:
		Circle(int pointsNumber, int radius, int x, int y);
		void draw(const Vector4D<uint8_t>& drawingColor, PixelsTable& pixelsTable) override;
		void move(double deltaTime) override;
};

#endif