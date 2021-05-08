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
    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
    void drawCartesianAxies(SDL_Renderer* renderer, int screenWidth, int screenHeight, Vector3D<int>* color);
}

#endif
