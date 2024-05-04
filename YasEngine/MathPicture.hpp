#ifndef MATH_PICTURE_HPP
#define MATH_PICTURE_HPP
#include "PointsGenerator.hpp"

class MathPicture
{
	public:
		MathPicture(std::map<int, float>* numbers, PointsGenerator* pointsGenerator, PointsSet* npointsSet)
		{
			this->basePointsFuel = static_cast<int>(numbers->size());
			this->pointsGenerator = pointsGenerator;
			this->numbers = numbers;
			this->floatNumbers = nullptr;
			generatePoints();
		}
		MathPicture(std::map<float, float>* floatNumbers, PointsGenerator* pointsGenerator, PointsSet* npointsSet)
		{
			this->basePointsFuel = static_cast<int>(floatNumbers->size());
			this->pointsGenerator = pointsGenerator;
			this->numbers = nullptr;
			this->floatNumbers = floatNumbers;
			generatePoints();
		}
		void generatePoints()
		{
			if (numbers != nullptr)
			{
				pointsSet = pointsGenerator->generatePoints(static_cast<int>(numbers->size()), numbers);
			}
			if (floatNumbers != nullptr)
			{
				pointsSet = pointsGenerator->generateFloatPoints(static_cast<int>(floatNumbers->size()), floatNumbers);
			}

		}
		int basePointsFuel = 0;
		int minimalPointsFuel = 0;
		PointsGenerator* pointsGenerator;
		PointsSet* pointsSet;
		std::map<int, float>* numbers;
		std::map<float, float>* floatNumbers;
};

#endif
