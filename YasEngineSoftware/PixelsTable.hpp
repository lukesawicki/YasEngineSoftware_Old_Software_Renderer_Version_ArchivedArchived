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
			Vector2D<int> windowDimensions;
			PixelsTable(int width, int height, const Vector4D<uint8_t>& defaultColor);
			PixelsTable(const PixelsTable& originalPixelsTable, const Vector4D<uint8_t>& defaultColor);
			~PixelsTable();
			void clearColor(const Vector4D<uint8_t>& drawingColor);
			void drawPoint(int x, int y, const Vector4D<uint8_t>& drawingColor);
			void cartesianPositionToWindow(int& x, int& y);
	};

#endif
