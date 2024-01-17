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
			this->floatNumbers = nullptr;
			generatePoints();
		}
		MathPicture(int maxNtoCalculateNumbers, std::map<float, float>* floatNumbers, PointsGenerator* pointsGenerator, PointsSet* npointsSet)
		{
			this->basePointsFuel = floatNumbers->size();
			this->maximumPointsFuel = floatNumbers->size();
			this->pointsGenerator = pointsGenerator;
			this->numbers = nullptr;
			this->floatNumbers = floatNumbers;
			generatePoints();
		}
		void generatePoints()
		{
			if (numbers != nullptr)
			{
				pointsSet = pointsGenerator->generatePoints(numbers->size(), numbers);
			}
			if (floatNumbers != nullptr)
			{
				pointsSet = pointsGenerator->generateFloatPoints(floatNumbers->size(), floatNumbers);
			}

		}
		int basePointsFuel = 0;
		int minimalPointsFuel = 0;
		int maximumPointsFuel = 0;
		PointsGenerator* pointsGenerator;
		PointsSet* pointsSet;
		std::map<int, float>* numbers;
		std::map<float, float>* floatNumbers;
};

#endif



// surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(sinusPoints->points, sinusPoints->pointsNumber, verticesHarvested, BLUE, true);