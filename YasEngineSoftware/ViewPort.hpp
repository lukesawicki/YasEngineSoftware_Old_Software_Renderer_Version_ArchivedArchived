#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP
#include"Vector2D.hpp"
#include"Vector4D.hpp"
#include"PixelsTable.hpp"
#include"GameObject.hpp"
#include<SDL.h>

class ViewPort
{
	public:
		Vector2D<int> position;
		Vector2D<int> viewPortSizes;
		Uint8* pixels = nullptr;

		virtual void clearColor(const Vector4D<Uint8>& drawingColor) = 0;
		virtual void drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor) = 0;
		virtual void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor) = 0;
		virtual void drawPolygon(GameObject* polygon, PixelsTable& pixelsTable) = 0;

		//wywolac rysowanie lini czy punktu dla view portu czyli na swojej pozycji + pozycja view portu (pozycja LEFT TOP point i RIGHT BOTTOM POINT(wyliczony na podstawie rozmiarow))

};

#endif

//Uint8* pixels = nullptr;
//Vector2D<int> windowDimensions;
//
//PixelsTable(int x, int y, int width, int height, const PixelsTable& originalPixelsTable, const Vector4D<Uint8>& defaultColor);
//PixelsTable(const Vector2D<int>& position, int width, int height, const PixelsTable& originalPixelsTable, const Vector4D<Uint8>& defaultColor);
//~PixelsTable();
//void clearColor(const Vector4D<Uint8>& drawingColor);
//void drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor);
//void cartesianPositionToWindow(int& x, int& y);
//};