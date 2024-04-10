#include"SinePointsGenerator.hpp"

PointsSet* SinePointsGenerator::generatePoints(int numberOfNumbers, std::map<int, float>* numbers)
{
	this->pointsNumber = numberOfNumbers;
	Vector2D<float>* points = new Vector2D<float>[pointsNumber];
	float divider = static_cast<float>(pointsNumber);
	float maximumXvalue = 2.0F * PI;
	float additionalFactor = 50.0F;
	float step = (maximumXvalue / divider);

	for (int i = 0; i < pointsNumber; i++)
	{
		float x = i * step;
		float y = sin(x);

		// numbers.push_back(y);

		points[i].x = x * additionalFactor; // round(x * additionalFactor);
		points[i].y = y * additionalFactor; // round(y * additionalFactor);
	}

	PointsSet* pointsSet = new PointsSet();
	pointsSet->points = points;
	pointsSet->pointsNumber = pointsNumber;
	return pointsSet;
}

PointsSet* SinePointsGenerator::generateFloatPoints(int numberOfNumbers, std::map<float, float>* numbers)
{
	this->pointsNumber = numberOfNumbers;
	Vector2D<float>* points = new Vector2D<float>[pointsNumber];
	int additionalFactor = 50;
	int i = 0;
	for (std::pair<float, float> pair : *numbers)
	{
		points[i].x = pair.first * additionalFactor; // round(x * additionalFactor);
		points[i].y = pair.second * additionalFactor; // round(y * additionalFactor);
		i++;
	}

	PointsSet* pointsSet = new PointsSet();
	pointsSet->points = points;
	pointsSet->pointsNumber = pointsNumber;
	return pointsSet;
}