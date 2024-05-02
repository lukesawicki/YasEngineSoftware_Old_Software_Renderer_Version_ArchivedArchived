#include"PrimeNumbersPointsGenerator.hpp"
#include "YasGraphicsLibrary.hpp"

PointsSet* PrimeNumbersPointsGenerator::generatePoints(int numberOfNumbers, std::map<int, float>* numbers)
{
	this->pointsNumber = numberOfNumbers;

	Vector2D<float>* points = new Vector2D<float>[pointsNumber * 2];

	int j = 0;
	for (int i = 1; i < (pointsNumber * 2) - 1; i += 2)
	{
		// float n = // (*numbers).at(i);
		points[i].x = numbers->at(j++);//primeNumbers.at(j++));//100.0F; // static_cast<float>(fibonacci.at(j++));
	}

	j = 0;
	for (int i = 1; i < pointsNumber * 2 - 1; i += 2)
	{
		Vector2D<float>::rotateVectorOverTheAngle(&points[i], static_cast<int>(numbers->at(j++)) * (PI / 180.0F));
	}

	PointsSet* pointsSet = new PointsSet();
	pointsSet->points = points;
	pointsSet->pointsNumber = pointsNumber;
	return pointsSet;
}

PointsSet* PrimeNumbersPointsGenerator::generateFloatPoints(int numberOfNumbers, std::map<float, float>* numbers)
{
	return nullptr;
}
