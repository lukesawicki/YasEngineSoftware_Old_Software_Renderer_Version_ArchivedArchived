#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include<vector>
#include<SDL.h>
#include"GameObject.hpp"
#include"Vector2D.hpp"
#include"Vector4D.hpp"
#include"PixelsTable.hpp"

class PixelsTable;
class GameObject;

const float PI = 3.141592F;
const Uint8 NUMBER_OF_COLORS = 4;
const Uint8 RGB_FORMAT = 3;
const Uint8 RGBA_FORMAT = 4;

const Uint8 RED_POSITION = 0;
const Uint8 GREEN_POSITION = 1;
const Uint8 BLUE_POSITION = 2;
const Uint8 ALPHA_POSITION = 3;

const Vector4D<Uint8> RED(255, 0, 0, 0);
const Vector4D<Uint8> GREEN(0, 255, 0, 0);
const Vector4D<Uint8> BLUE(0, 0, 255, 0);
const Vector4D<Uint8> BLACK(0, 0, 0, 255);
//const Vector4D<Uint8> ALT_BLACK(0, 0, 0, 0);
const Vector4D<Uint8> WHITE(255, 255, 255, 255);
const Vector4D<Uint8> YELLOW(255, 255, 0, 255);

void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor);

void drawPolygon(GameObject* polygon, PixelsTable& pixelsTable);

Vector2D<float>* generateVerticesFromNumbers(const std::vector<int>& numbers);

void drawNumbersAsGroupOfLines(Vector2D<float>* vertices, int maximumNumberOfVertices, const Vector4D<Uint8>& color, bool areLinesContinuos, PixelsTable& pixelsTable);
void drawNumbersAsGroupOfLines(Vector2D<float>* vertices, int maximumNumberOfVertices, PixelsTable& pixelsTable);

void drawNumbersAsPolyline(Vector2D<float>* vertices, int maximumNumberOfVertices, PixelsTable& pixelsTable);

void drawPolygonDirection(GameObject* polygon, PixelsTable& pixelsTable);

void swapVectors(Vector2D<int>& point0, Vector2D<int>& point1);

void horizontalLineOnWholeScreen(PixelsTable& pixelsTable, int y, Vector4D<Uint8> color);

void verticalLineOnWholeScreen(PixelsTable& pixelsTable, int x, Vector4D<Uint8> color);

void drawCartesianAxies(PixelsTable& pixelsTable);

void drawCrossHair(float x, float y, PixelsTable& pixelsTable, bool isFullScreen);

void drawHorizontalLine(PixelsTable& pixelsTable, int x0, int x1, int y, Vector4D<Uint8> color);

void drawVerticalLine(PixelsTable& pixelsTable, int y0, int y1, int x, Vector4D<Uint8> color);
    
int xyPixelToArrayPosition(Vector2D<int>& point, int windowWidth);
int xyPixelToArrayPosition(int x, int y, int windowWidth);

void windowPositionToCartesianPosition(float& x, float& y, Vector2D<int>* windowDimensions);

void drawMandelbrotSet();

void drawRectangle(PixelsTable& pixelsTable, int x, int y, int width, int height, Vector4D<Uint8> color);
#endif
