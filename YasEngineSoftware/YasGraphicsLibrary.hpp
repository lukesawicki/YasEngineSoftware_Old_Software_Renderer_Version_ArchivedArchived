#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include<cmath>
#include<iostream>
#include <GLFW/glfw3.h>
#include"Vector2D.hpp"
#include"Vector3D.hpp"
#include"Vector4D.hpp"
#include "PixelsTable.hpp"

class PixelsTable;

namespace YasGL
{
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

    const float dl = 3.125e-3F;

    enum class LineSlope { GENTLE, STEEP, HORIZONTAL, VERTICAL };
    enum class PointsOrder { NORMAL, REVERSE };
    enum class PositionInSpace { Q0, Q1, Q2, Q3, Q10, Q23, Q12, Q03, Q123_230, Q12_V, Q10_H };

    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, PixelsTable& pixelsTable, const Vector4D<uint8_t>& drawingColor);
    void swapVectors(Vector2D<int>*& point0, Vector2D<int>*& point1);

    void drawCartesianAxies(PixelsTable& pixelsTable);
    int xyPixelToArrayPosition(Vector2D<int>* point, int windowWidth);
    int xyPixelToArrayPosition(int x, int y, int windowWidth);
}

#endif
