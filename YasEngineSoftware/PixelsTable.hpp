#ifndef PIXELSTABLE_HPP
#define PIXELSTABLE_HPP
#include<SDL.h>
#include "YasVector2D.hpp"
#include "YasVector4D.hpp"
#include "YasGraphicsLibrary.hpp"

class PixelsTable
{
	public:
		Uint8* pixels = nullptr;
		YasVector2D<int> windowDimensions;
		PixelsTable(int width, int height, const YasVector4D<Uint8>& defaultColor);
		PixelsTable(const PixelsTable& originalPixelsTable, const YasVector4D<Uint8>& defaultColor);
		~PixelsTable();
		void clearColor(const YasVector4D<Uint8>& drawingColor);
		void drawPoint(int x, int y, const YasVector4D<Uint8>& drawingColor);
		void cartesianPositionToWindow(int& x, int& y);
};

#endif
