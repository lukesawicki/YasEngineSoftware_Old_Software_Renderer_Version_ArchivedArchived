#ifndef MATH_PICTURE_HPP
#define MATH_PICTURE_HPP
#include<map>
#include "PointsGenerator.hpp"
class MathPicture
{
	public:
		MathPicture(std::map<int, float>* numbers, PointsGenerator* pointsGenerator, PointsSet* nPointsSet);
		MathPicture(std::map<float, float>* floatNumbers, PointsGenerator* pointsGenerator, PointsSet* nPointsSet);
		void generatePoints();
		
		int basePointsFuel = 0;
		int minimalPointsFuel = 0;
		PointsGenerator* pointsGenerator;
		PointsSet* pointsSet;
		std::map<int, float>* numbers;
		std::map<float, float>* floatNumbers;
};

#endif
