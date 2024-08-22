#ifndef PIXELSTABLE_HPP
#define PIXELSTABLE_HPP
#include<SDL.h>
#include"Vector2D.hpp"
#include"Vector4D.hpp"


class PixelsTable
{
  public:
    Uint8* pixels = nullptr;
    Vector2D<int> windowDimensions;
    PixelsTable(int width, int height, const Vector4D<Uint8>& defaultColor);
    PixelsTable(const PixelsTable& originalPixelsTable, const Vector4D<Uint8>& defaultColor);
    ~PixelsTable();
    void clearColor(const Vector4D<Uint8>& drawingColor);
    void drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor);
    void cartesianPositionToWindow(int& x, int& y);
};

#endif
