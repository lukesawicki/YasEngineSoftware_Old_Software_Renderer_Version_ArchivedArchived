#include"MathematicsFunSurface.hpp"

//derived
//Vector2D<int> position;
//Vector2D<int> viewPortSizes;
//Uint8* pixels = nullptr;

MathematicsFunSurface::MathematicsFunSurface(int x, int y, int width, int height, const Vector4D<Uint8>& defaultColor)
{
	position.x = x;
	position.y = y;
	viewPortSizes.x = width;
	viewPortSizes.y = height;
	this->pixels = new Uint8[viewPortSizes.x * viewPortSizes.y * NUMBER_OF_COLORS];
	clearColor(defaultColor);

}

MathematicsFunSurface::MathematicsFunSurface(Vector2D<int> position, int width, int height, const Vector4D<Uint8>& defaultColor)
{
	this->position.x = position.x;
	this->position.y = position.y;
	viewPortSizes.x = width;
	viewPortSizes.y = height;
	this->pixels = new Uint8[viewPortSizes.x * viewPortSizes.y * NUMBER_OF_COLORS];
	clearColor(defaultColor);
}

MathematicsFunSurface::~MathematicsFunSurface()
{
	delete[] pixels;
}

void MathematicsFunSurface::clearColor(const Vector4D<Uint8>& drawingColor)
{
	for (int y = 0; y < viewPortSizes.y; y++)
	{
		for (int x = 0; x < viewPortSizes.x; x++)
		{
			pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + RED_POSITION] = drawingColor.x; // windowDimensions->x <- WINDOW WIDTH
			pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + GREEN_POSITION] = drawingColor.y;
			pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + BLUE_POSITION] = drawingColor.z;
			pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + ALPHA_POSITION] = drawingColor.w;
		}
	}
}

void MathematicsFunSurface::drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor)
{
	cartesianPositionToWindow(x, y);
	if (x >= 0 && x < viewPortSizes.x && y >= 0 && y < viewPortSizes.y)
	{
		pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + RED_POSITION] = drawingColor.x; // windowDimensions->x <- WINDOW WIDTH
		pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + GREEN_POSITION] = drawingColor.y;
		pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + BLUE_POSITION] = drawingColor.z;
		pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + ALPHA_POSITION] = drawingColor.w;
	}
}

void MathematicsFunSurface::drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor)
{
}

void MathematicsFunSurface::drawPolygon(GameObject* polygon, PixelsTable& pixelsTable)
{
}
