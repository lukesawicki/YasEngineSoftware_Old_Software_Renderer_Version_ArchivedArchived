#include"PrimeNumbersPointsGenerator.hpp"
#include "YasGraphicsLibrary.hpp"

std::vector<int> PrimeNumbersPointsGenerator::numbers;

PointsSet* PrimeNumbersPointsGenerator::generatePoints()
{
	pointsNumber = 1000;

	std::vector<int> primeNumbers = generatePrimeNumbersLessThanN(pointsNumber);
    for(int i=0; i<static_cast<int>(primeNumbers.size()); i++)
    {
        numbers.push_back((primeNumbers.at(i)));
    }

	pointsNumber = primeNumbers.size();

	Vector2D<float>* points = new Vector2D<float>[pointsNumber * 2];

	int j = 0;
	for (int i = 1; i < (pointsNumber * 2) - 1; i += 2)
	{
		points[i].x = static_cast<float>(primeNumbers.at(j++));//100.0F; // static_cast<float>(fibonacci.at(j++));
	}

	j = 0;
	for (int i = 1; i < pointsNumber * 2 - 1; i += 2)
	{
		Vector2D<float>::rotateVectorOverTheAngle(&points[i], static_cast<int>(primeNumbers.at(j++)) * (PI / 180.0F));
	}

	PointsSet* pointsSet = new PointsSet();
	pointsSet->points = points;
	pointsSet->pointsNumber = pointsNumber;
	return pointsSet;
}