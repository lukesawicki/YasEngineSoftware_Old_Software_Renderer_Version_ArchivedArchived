#ifndef MATHEMATICSFUNSURFACE_HPP
#define MATHEMATICSFUNSURFACE_HPP
#include"ViewPort.hpp"

class Tile : public ViewPort
{
	public:
		void cartesianPositionToWindow(int& x, int& y)
		{
			x = x + static_cast<int>(0.5F * viewPortSizes.x);
			y = -y + static_cast<int>(0.5F * viewPortSizes.y);
		}
		Tile();
		Tile(int x, int y, int width, int height, const Vector4D<Uint8>& defaultColor);
		Tile(Vector2D<int> position, int width, int height, const Vector4D<Uint8>& defaultColor);
		void setPositions(int x, int y);
		void setSizes(int width, int height);
		void setColor(const Vector4D<Uint8>& defaultColor);
		void createPixelsTable();
		~Tile();
		void clearColor(const Vector4D<Uint8>& drawingColor) override;
		void drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor) override;
		void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, const Vector4D<Uint8>& drawingColor)  override;
		void drawPolygon(GameObject* polygon)  override;
		void copyPixelsInToPIxelTable(PixelsTable& pixelsTable);
		void copyPixelsInToPIxelTable(PixelsTable& pixelsTable, bool cartesian);

		void horizontalLineOnScreen(int y, Vector4D<Uint8> color)
		{
			int maxX = static_cast<int>(0.5F * viewPortSizes.x);
			for (int i = -maxX; i < maxX; i++) //X
			{
				drawPoint(i, y, color);
			}
		}

		void verticalLineOnScreen(int x, Vector4D<Uint8> color)
		{
			int maxY = static_cast<int>(0.5F * viewPortSizes.y);
			for (int i = -maxY; i < maxY; i++) //X
			{
				drawPoint(x, i, color);
			}
		}
};

#endif