#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include<cmath>
#include<iostream>
#include <GLFW/glfw3.h>
#include"Vector2D.hpp"
#include"Vector4D.hpp"
#include "PixelsTable.hpp"
#include "Polygonn.hpp"

class PixelsTable;

namespace YasGL
{
    const float PI = 3.141592F;
    const uint8_t NUMBER_OF_COLORS = 4;
    const uint8_t RGB_FORMAT = 3;
    const uint8_t RGBA_FORMAT = 4;

    const uint8_t RED_POSITION = 0;
    const uint8_t GREEN_POSITION = 1;
    const uint8_t BLUE_POSITION = 2;
    const uint8_t ALPHA_POSITION = 3;

    const Vector4D<uint8_t> RED(255, 0, 0, 0);
    const Vector4D<uint8_t> GREEN(0, 255, 0, 0);
    const Vector4D<uint8_t> BLUE(0, 0, 255, 0);
    const Vector4D<uint8_t> BLACK(0, 0, 0, 255);
    const Vector4D<uint8_t> WHITE(255, 255, 255, 255);
    const Vector4D<uint8_t> YELLOW(255, 255, 0, 255);

    void drawLine(const Vector2D<int>& point0, const Vector2D<int>& point1, PixelsTable& pixelsTable, const Vector4D<uint8_t>& drawingColor);

    void drawPolygon(YasGL::Polygonn* polygon, const Vector4D<uint8_t>& color, PixelsTable& pixelsTable);

    void swapVectors(Vector2D<int>& point0, Vector2D<int>& point1);

    void drawCartesianAxies(PixelsTable& pixelsTable);
    int xyPixelToArrayPosition(Vector2D<int>& point, int windowWidth);
    int xyPixelToArrayPosition(int x, int y, int windowWidth);
}

#endif
