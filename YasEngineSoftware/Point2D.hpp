#ifndef POINT2D_HPP
#define POINT2D_HPP

#include"Vector2D.hpp"
#include "YasGraphicsLibrary.hpp"

class Point2D
{
	public:
		Point2D(Vector2D<int>* position);
		Point2D(int x0, int y0, int x1, int y1);
		Point2D(Vector2D<int>* position, YasGL::Color* color);
		Point2D(int x0, int y0, int x1, int y1, YasGL::Color* color);
		
		Vector2D<int>* position;
		YasGL::Color* color;
};

#endif
