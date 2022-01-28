#include"PixelsTAble.hpp"

PixelsTable::PixelsTable(int width, int height, const Vector4D<uint8_t>& defaultColor)
{
	this->windowDimensions.x = width;
	this->windowDimensions.y = height;
	this->pixels = new uint8_t[windowDimensions.x * windowDimensions.y * YasGL::NUMBER_OF_COLORS];
	clearColor(defaultColor);
}

PixelsTable::~PixelsTable()
{
	delete[] pixels;
}

void PixelsTable::clearColor(const Vector4D<uint8_t>& drawingColor)
{
	for (int y = 0; y < windowDimensions.y; y++)
	{
		for (int x = 0; x < windowDimensions.x; x++)
		{
			pixels[YasGL::NUMBER_OF_COLORS * (y * windowDimensions.x + x) + YasGL::RED_POSITION] = drawingColor.x; // windowDimensions->x <- WINDOW WIDTH
			pixels[YasGL::NUMBER_OF_COLORS * (y * windowDimensions.x + x) + YasGL::GREEN_POSITION] = drawingColor.y;
			pixels[YasGL::NUMBER_OF_COLORS * (y * windowDimensions.x + x) + YasGL::BLUE_POSITION] = drawingColor.z;
			pixels[YasGL::NUMBER_OF_COLORS * (y * windowDimensions.x + x) + YasGL::ALPHA_POSITION] = drawingColor.w;
		}
	}
}

void PixelsTable::drawPoint(int x, int y, const Vector4D<uint8_t>& drawingColor)
{
	cartesianPositionToWindow(x, y);
	if (x >= 0 && x < windowDimensions.x && y >= 0 && y < windowDimensions.y)
	{
		pixels[YasGL::NUMBER_OF_COLORS * (y * windowDimensions.x + x) + YasGL::RED_POSITION] = drawingColor.x; // windowDimensions->x <- WINDOW WIDTH
		pixels[YasGL::NUMBER_OF_COLORS * (y * windowDimensions.x + x) + YasGL::GREEN_POSITION] = drawingColor.y;
		pixels[YasGL::NUMBER_OF_COLORS * (y * windowDimensions.x + x) + YasGL::BLUE_POSITION] = drawingColor.z;
		pixels[YasGL::NUMBER_OF_COLORS * (y * windowDimensions.x + x) + YasGL::ALPHA_POSITION] = drawingColor.w;
	}
}

void PixelsTable::drawPoint(Vector2D<int>* point, const Vector4D<uint8_t>& drawingColor)
{
	cartesianPositionToWindow(point);
	if (point->x >= 0 && point->x < windowDimensions.x && point->y >= 0 && point->y < windowDimensions.y)
	{
		pixels[YasGL::NUMBER_OF_COLORS * (point->y * windowDimensions.x + point->x) + YasGL::RED_POSITION] = drawingColor.x; // windowDimensions->x <- WINDOW WIDTH
		pixels[YasGL::NUMBER_OF_COLORS * (point->y * windowDimensions.x + point->x) + YasGL::GREEN_POSITION] = drawingColor.y;
		pixels[YasGL::NUMBER_OF_COLORS * (point->y * windowDimensions.x + point->x) + YasGL::BLUE_POSITION] = drawingColor.z;
		pixels[YasGL::NUMBER_OF_COLORS * (point->y * windowDimensions.x + point->x) + YasGL::ALPHA_POSITION] = drawingColor.w;
	}
}

void PixelsTable::cartesianPositionToWindow(int& x, int& y)
{
	x = x + static_cast<int>(0.5F * windowDimensions.x);
	y = y + static_cast<int>(0.5F * windowDimensions.y);
}

void PixelsTable::cartesianPositionToWindow(Vector2D<int>* point)
{
	point->x = point->x + static_cast<int>(0.5F * windowDimensions.x);
	point->y = point->y + static_cast<int>(0.5F * windowDimensions.y);
}
