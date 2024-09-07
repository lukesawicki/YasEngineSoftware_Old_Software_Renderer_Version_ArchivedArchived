#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include <SDL.h>

#include <vector>

#include "game_object.hpp"
#include "pixels_table.hpp"
#include "vector_2d.hpp"
#include "color.hpp"

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

const Color kRed(255, 0, 0, 0);
const Color kGreen(0, 255, 0, 0);
const Color kBlue(0, 0, 255, 0);
const Color kBlack(0, 0, 0, 255);
const Color kWhite(255, 255, 255, 0);
const Color kYellow(255, 255, 0, 0);
const Color kLightBlue(0, 255, 255, 0);
const Color kPurple(255, 0, 255, 0);
const Color kXportal(255, 77, 0, 0);
const Color kPolygon(250, 180, 10, 0);

void DrawLine(const Vector2D& point_0, const Vector2D& point_1,
              PixelsTable& pixels_table, const Color& drawing_color);

void DrawPolygon(GameObject* polygon, PixelsTable& pixels_table);

Vector2D* GenerateVerticesFromNumbers(const std::vector<int>& numbers);

void DrawNumbersAsGroupOfLines(Vector2D* vertices,
                               int maximum_number_of_vertices,
                               const Color& color,
                               bool are_lines_continuous,
                               PixelsTable& pixels_table);

void DrawNumbersAsGroupOfLines(Vector2D* vertices,
                               int maximum_number_of_vertices,
                               PixelsTable& pixels_table);

void DrawNumbersAsLineStrip(Vector2D* vertices,
                           int maximum_number_of_vertices,
                           PixelsTable& pixels_table);void DrawPolygonDirection(GameObject* polygon, PixelsTable& pixels_table);

void SwapVectors(Vector2D& point_0, Vector2D& point_1);

void HorizontalLineOnWholeScreen(PixelsTable& pixels_table, int y,
                                 Color color);

void VerticalLineOnWholeScreen(PixelsTable& pixels_table, int x,
                               Color color);

void DrawCartesianAxes(PixelsTable& pixels_table);

void DrawCrossHair(float x, float y, PixelsTable& pixels_table,
                   bool is_full_screen);

void DrawCrossHair(float x, float y, PixelsTable& pixels_table,
                   bool is_full_screen, Color color);

void DrawHorizontalLine(PixelsTable& pixels_table, int x_0, int x_1, int y,
                        Color color);

void DrawVerticalLine(PixelsTable& pixels_table, int y_0, int y_1, int x,
                      Color color);

int ScreenPixelPositionToArrayPosition(Vector2D& point, int window_width);

int ScreenPixelPositionToArrayPosition(int x, int y, int window_width);

void WindowPositionToCartesianPosition(float& x, float& y,
                                       Dimensions2D* window_dimensions);

void DrawMandelbrotSet();

void DrawRectangle(PixelsTable& pixels_table, int x, int y, int width,
                   int height, Color color);

#endif
