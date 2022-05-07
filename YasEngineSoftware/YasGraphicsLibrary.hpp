#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include<cmath>
#include<iostream>
#include <GLFW/glfw3.h>
#include"YasVector2D.hpp"
#include"YasVector4D.hpp"
#include "PixelsTable.hpp"
#include "YasPolygon.hpp"

class PixelsTable;

const float PI = 3.141592F;
const uint8_t NUMBER_OF_COLORS = 4;
const uint8_t RGB_FORMAT = 3;
const uint8_t RGBA_FORMAT = 4;

const uint8_t RED_POSITION = 0;
const uint8_t GREEN_POSITION = 1;
const uint8_t BLUE_POSITION = 2;
const uint8_t ALPHA_POSITION = 3;

const YasVector4D<uint8_t> RED(255, 0, 0, 0);
const YasVector4D<uint8_t> GREEN(0, 255, 0, 0);
const YasVector4D<uint8_t> BLUE(0, 0, 255, 0);
const YasVector4D<uint8_t> BLACK(0, 0, 0, 255);
const YasVector4D<uint8_t> WHITE(255, 255, 255, 255);
const YasVector4D<uint8_t> YELLOW(255, 255, 0, 255);

void drawLine(const YasVector2D<float>& point0, const YasVector2D<float>& point1, PixelsTable& pixelsTable, const YasVector4D<uint8_t>& drawingColor);

void drawPolygon(YasPolygon* polygon, PixelsTable& pixelsTable);

void drawPolygonDirection(YasPolygon* polygon, PixelsTable& pixelsTable);

void swapVectors(YasVector2D<int>& point0, YasVector2D<int>& point1);

void horizontalLineOnScreen(PixelsTable& pixelsTable, int y, YasVector4D<uint8_t> color);

void verticalLineOnScreen(PixelsTable& pixelsTable, int x, YasVector4D<uint8_t> color);

void drawCartesianAxies(PixelsTable& pixelsTable);

void drawCrossOnScreen(float x, float y, PixelsTable& pixelsTable);
    
int xyPixelToArrayPosition(YasVector2D<int>& point, int windowWidth);
int xyPixelToArrayPosition(int x, int y, int windowWidth);

//void windowPositionToCartesianPosition(double& x, double& y, YasVector2D<int>* windowDimensions);
void windowPositionToCartesianPosition(float& x, float& y, YasVector2D<int>* windowDimensions);

#endif
