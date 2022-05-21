#ifndef MATHEMATICSFUNSURFACE_HPP
#define MATHEMATICSFUNSURFACE_HPP
#include"ViewPort.hpp"

class MathematicsFunSurface : public ViewPort
{
	//derived
	//Vector2D<int> position;
	//Vector2D<int> viewPortSizes;
	//Uint8* pixels = nullptr;
	public:
		void cartesianPositionToWindow(int& x, int& y)
		{
			x = x + static_cast<int>(0.5F * viewPortSizes.x);
			y = y + static_cast<int>(0.5F * viewPortSizes.y);
		}
		MathematicsFunSurface(int x, int y, int width, int height, const Vector4D<Uint8>& defaultColor);
		MathematicsFunSurface(Vector2D<int> position, int width, int height, const Vector4D<Uint8>& defaultColor);
		~MathematicsFunSurface();
		void clearColor(const Vector4D<Uint8>& drawingColor) override;
		void drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor) override;
		void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor)  override;
		void drawPolygon(GameObject* polygon, PixelsTable& pixelsTable)  override;
};

#endif