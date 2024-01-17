#ifndef MATH_PICTURE_HPP
#define MATH_PICTURE_HPP
#include "PointsGenerator.hpp"

class MathPicture
{
	public:
		MathPicture(int maxNtoCalculateNumbers, std::map<int, float>* numbers, PointsGenerator* pointsGenerator, PointsSet* npointsSet)
		{
			this->basePointsFuel = numbers->size();
			this->maximumPointsFuel = numbers->size();
			this->pointsGenerator = pointsGenerator;
			this->numbers = numbers;
			generatePoints();
		}
		void generatePoints()
		{
			pointsSet = pointsGenerator->generatePoints(numbers->size(), numbers);
		}
		int basePointsFuel = 0;
		int minimalPointsFuel = 0;
		int maximumPointsFuel = 0;
		PointsGenerator* pointsGenerator;
		PointsSet* pointsSet;
		std::map<int, float>* numbers;
};

#endif



// surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(sinusPoints->points, sinusPoints->pointsNumber, verticesHarvested, BLUE, true);