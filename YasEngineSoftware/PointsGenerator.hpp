#ifndef POINTSGENERATOR_HPP
#define POINTSGENERATOR_HPP
#include "Vector2D.hpp"

class PointsGenerator
{
	public:
		int pointsNumber = 0;
		virtual Vector2D<float>* generatePoints() = 0;
		
};

#endif
