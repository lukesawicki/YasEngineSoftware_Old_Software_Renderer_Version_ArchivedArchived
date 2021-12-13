#ifndef PIXELSTABLE_HPP
#define PIXELSTABLE_HPP
#include <GLFW/glfw3.h>
#include "Vector2D.hpp"
#include "Vector4D.hpp"
#include "YasGraphicsLibrary.hpp"

class PixelsTable
{
	public:
		uint8_t* pixels = nullptr;
		Vector2D<int>* windowDimensions = nullptr;

		PixelsTable(int width, int height, Vector4D<uint8_t>* defaultColor);
		~PixelsTable();

		void clearColor(Vector4D<uint8_t>* drawingColor);
		void drawPoint(int x, int y, Vector4D<uint8_t>* drawingColor);
		void drawPoint(Vector2D<int>* point, Vector4D<uint8_t>* drawingColor);

		void cartesianPositionToWindow(int& x, int& y);
		void cartesianPositionToWindow(Vector2D<int>* point);
};

#endif PIXELSTABLE_HPP
