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

void DrawLine(const Vector2D<float>& point_0, const Vector2D<float>& point_1,
              PixelsTable& pixels_table, const Vector4D<Uint8>& drawing_color);

void DrawPolygon(GameObject* polygon, PixelsTable& pixels_table);

Vector2D<float>* GenerateVerticesFromNumbers(const std::vector<int>& numbers);

void DrawNumbersAsGroupOfLines(Vector2D<float>* vertices,
                               int current_number_of_vertices,
                               const Vector4D<Uint8>& color,
                               bool are_lines_continuous,
                               PixelsTable& pixels_table);

void DrawPolygonDirection(GameObject* polygon, PixelsTable& pixels_table);

void SwapVectors(Vector2D<int>& point_0, Vector2D<int>& point_1);

void HorizontalLineOnWholeScreen(PixelsTable& pixels_table, int y,
                                 Vector4D<Uint8> color);

void VerticalLineOnWholeScreen(PixelsTable& pixels_table, int x,
                               Vector4D<Uint8> color);

void DrawCartesianAxes(PixelsTable& pixels_table);

void DrawCrossHair(float x, float y, PixelsTable& pixels_table,
                   bool is_full_screen);

void DrawCrossHair(float x, float y, PixelsTable& pixels_table,
                   bool is_full_screen, Vector4D<Uint8> color);

void DrawHorizontalLine(PixelsTable& pixels_table, int x_0, int x_1, int y,
                        Vector4D<Uint8> color);

void DrawVerticalLine(PixelsTable& pixels_table, int y_0, int y_1, int x,
                      Vector4D<Uint8> color);

int ScreenPixelPositionToArrayPosition(Vector2D<int>& point, int window_width);

int ScreenPixelPositionToArrayPosition(int x, int y, int window_width);

void WindowPositionToCartesianPosition(float& x, float& y,
                                       Vector2D<int>* window_dimensions);

void DrawMandelbrotSet();

void DrawRectangle(PixelsTable& pixels_table, int x, int y, int width,
                   int height, Vector4D<Uint8> color);

#endif
