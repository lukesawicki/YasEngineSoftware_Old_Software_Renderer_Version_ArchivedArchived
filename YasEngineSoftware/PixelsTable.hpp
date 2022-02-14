#ifndef PIXELSTABLE_HPP
#define PIXELSTABLE_HPP
#include <GLFW/glfw3.h>
#include "YasVector2D.hpp"
#include "YasVector4D.hpp"
#include "YasGraphicsLibrary.hpp"

class PixelsTable
{
	public:
		uint8_t* pixels = nullptr;
		YasVector2D<int> windowDimensions;
		PixelsTable(int width, int height, const YasVector4D<uint8_t>& defaultColor);
		PixelsTable(const PixelsTable& originalPixelsTable, const YasVector4D<uint8_t>& defaultColor);
		~PixelsTable();
		void clearColor(const YasVector4D<uint8_t>& drawingColor);
		void drawPoint(int x, int y, const YasVector4D<uint8_t>& drawingColor);
		void cartesianPositionToWindow(int& x, int& y);
};

#endif
