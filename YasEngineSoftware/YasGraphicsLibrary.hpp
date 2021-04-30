#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include<cmath>
#include<SDL.h>
#include"Vector2D.hpp"


namespace YasGL
{
    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
}

#endif
