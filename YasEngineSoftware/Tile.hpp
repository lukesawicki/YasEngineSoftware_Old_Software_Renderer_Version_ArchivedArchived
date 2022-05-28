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
		void drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor, bool cartesian);
		void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, const Vector4D<Uint8>& drawingColor)  override;
		void drawPolygon(GameObject* polygon)  override;
		void drawPattern(int pattern, const Vector4D<Uint8>& drawingColor);
		void copyPixelsInToPIxelTable(PixelsTable& pixelsTable);
		void copyPixelsInToPIxelTable(PixelsTable& pixelsTable, bool cartesian);

		void drawTop();
		void drawRight();
		void drawBottom();
		void drawLeft();
		void drawLeftTopCorner();
		void drawRightTopCorner();
		void drawRightBottomCorner();
		void drawLeftBottomCorner();

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

		void horizontalLineOnViewport(int y, Vector4D<Uint8> color)
		{
			for (int i = 0; i < viewPortSizes.x; i++) //X
			{
				drawPoint(i, y, color, false);
			}
		}

		void verticalLineOnViewport(int x, Vector4D<Uint8> color)
		{
			for (int i = 0; i < viewPortSizes.y; i++) //X
			{
				drawPoint(x, i, color, false);
			}
		}
};

#endif