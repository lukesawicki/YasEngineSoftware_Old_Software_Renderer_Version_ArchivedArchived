#ifndef MATH_PICTURE_HPP
#define MATH_PICTURE_HPP
#include "PointsGenerator.hpp"

class MathPicture
{
	public: 
		int basePointsNumber = 0;
		int minimalPointsNumber = 0;//-64
		int maximumPointsNumber = 0
		PointsGenerator* pointsGenerator;
		PointsSet* pointsSet;
		

};

#endif



// surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(sinusPoints->points, sinusPoints->pointsNumber, verticesHarvested, BLUE, true);