#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include<cmath>
#include<SDL.h>
#include"Vector2D.hpp"
#include"Vector3D.hpp"


namespace YasGL
{
    void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* screen);
    void windowPositionToCartesian(Vector2D<int>* point, Vector2D<int>* screen);
    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, Uint32* pixels, Vector3D<int>* drawingColor, SDL_PixelFormat* pixelFormat, int windowWidth);
    void drawCartesianAxies(SDL_Renderer* renderer, int screenWidth, int screenHeight, Vector3D<int>* color);
    int xyPixelToArrayPosition(Vector2D<int>* point, int windowWidth);
    int xyPixelToArrayPosition(int x, int y, int windowWidth);
    void drawCircle(Uint32* pixels, Vector2D<int>* position, int& radius, int windowWidth, Vector3D<int>* drawingColor, SDL_PixelFormat* pixelFormat);
}

#endif
