#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "Vector2D.hpp"
#include "Vector4D.hpp"
#include"PixelsTable.hpp"
#include <GLFW/glfw3.h>

class Shape
{
	public:
		int* points = nullptr;
		virtual void draw(const Vector4D<uint8_t>& drawingColor, PixelsTable& pixelsTable) = 0;
		virtual void move(double deltaTime) = 0;

};

#endif
