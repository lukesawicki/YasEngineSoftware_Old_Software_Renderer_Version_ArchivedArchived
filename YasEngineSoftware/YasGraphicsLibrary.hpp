#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include<cmath>
#include<iostream>
#include <GLFW/glfw3.h>
#include"Vector2D.hpp"
#include"Vector3D.hpp"


namespace YasGL
{
    void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* screen);
    void windowPositionToCartesian(Vector2D<int>* point, Vector2D<int>* screen);
    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, unsigned char* pixels, Vector3D<unsigned char>* drawingColor, int windowWidth);
    void lukeDrawLineOctan0V1(Vector2D<int>* point0, Vector2D<int>* point1, unsigned char* pixels, Vector3D<unsigned char>* drawingColor, int windowWidth);
    void lukeDrawLineOctan0V2(Vector2D<int>* point0, Vector2D<int>* point1, unsigned char* pixels, Vector3D<unsigned char>* drawingColor, int windowWidth);
    void helsinkiDraw(Vector2D<int>* point0, Vector2D<int>* point1, unsigned char* pixels, Vector3D<unsigned char>* drawingColor, int windowWidth);
    void drawCartesianAxies(int screenWidth, int screenHeight, Vector3D<unsigned char>* drawingColor);
    int xyPixelToArrayPosition(Vector2D<int>* point, int windowWidth);
    int xyPixelToArrayPosition(int x, int y, int windowWidth);
    void drawCircle(unsigned char* pixels, Vector2D<int>* position, int& radius, int windowWidth, Vector3D<unsigned char>* drawingColor);
}

#endif
