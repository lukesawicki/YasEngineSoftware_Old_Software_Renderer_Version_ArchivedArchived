#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include <SDL.h>

#include <vector>

#include "game_object.hpp"
#include "pixels_table.hpp"
#include "vector_2d.hpp"
#include "vector_4d.hpp"

class PixelsTable;
class GameObject;

const float kPi = 3.141592F;
const Uint8 kNumberOfColors = 4;
const Uint8 kRgbFormat = 3;
const Uint8 kRgbaFormat = 4;

const Uint8 kRedPosition = 0;
const Uint8 kGreenPosition = 1;
const Uint8 kBluePosition = 2;
const Uint8 kAlphaPosition = 3;

const Vector4D<Uint8> kRed(255, 0, 0, 0);
const Vector4D<Uint8> kGreen(0, 255, 0, 0);
const Vector4D<Uint8> kBlue(0, 0, 255, 0);
const Vector4D<Uint8> kBlack(0, 0, 0, 255);
const Vector4D<Uint8> kWhite(255, 255, 255, 0);
const Vector4D<Uint8> kYellow(255, 255, 0, 0);
const Vector4D<Uint8> kLightBlue(0, 255, 255, 0);
const Vector4D<Uint8> kPurple(255, 0, 255, 0);
const Vector4D<Uint8> kXportal(255, 77, 0, 0);
const Vector4D<Uint8> kPolygon(250, 180, 10, 0);

void DrawLine(const Vector2D<float>& point0, const Vector2D<float>& point1,
              PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor);

void DrawPolygon(GameObject* polygon, PixelsTable& pixelsTable);

Vector2D<float>* GenerateVerticesFromNumbers(const std::vector<int>& numbers);

void DrawNumbersAsGroupOfLines(Vector2D<float>* vertices,
                               int maximumNumberOfVertices,
                               const Vector4D<Uint8>& color,
                               bool areLinesContinuos,
                               PixelsTable& pixelsTable);

void DrawNumbersAsGroupOfLines(Vector2D<float>* vertices,
                               int maximumNumberOfVertices,
                               PixelsTable& pixelsTable);

void DrawNumbersAsPolyline(Vector2D<float>* vertices,
                           int maximumNumberOfVertices,
                           PixelsTable& pixelsTable);

void DrawPolygonDirection(GameObject* polygon, PixelsTable& pixelsTable);

void SwapVectors(Vector2D<int>& point0, Vector2D<int>& point1);

void HorizontalLineOnWholeScreen(PixelsTable& pixelsTable, int y,
                                 Vector4D<Uint8> color);

void VerticalLineOnWholeScreen(PixelsTable& pixelsTable, int x,
                               Vector4D<Uint8> color);

void DrawCartesianAxies(PixelsTable& pixelsTable);

void DrawCrossHair(float x, float y, PixelsTable& pixelsTable,
                   bool isFullScreen);

void DrawCrossHair(float x, float y, PixelsTable& pixelsTable,
                   bool isFullScreen, Vector4D<Uint8> color);

void DrawHorizontalLine(PixelsTable& pixelsTable, int x0, int x1, int y,
                        Vector4D<Uint8> color);

void DrawVerticalLine(PixelsTable& pixelsTable, int y0, int y1, int x,
                      Vector4D<Uint8> color);

int ScreenPixelPositionToArrayPosition(Vector2D<int>& point, int windowWidth);

int ScreenPixelPositionToArrayPosition(int x, int y, int windowWidth);

void WindowPositionToCartesianPosition(float& x, float& y,
                                       Vector2D<int>* windowDimensions);

void DrawMandelbrotSet();

void DrawRectangle(PixelsTable& pixelsTable, int x, int y, int width,
                   int height, Vector4D<Uint8> color);

#endif
