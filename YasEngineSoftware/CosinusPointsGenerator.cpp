#include"CosinusPointsGenerator.hpp"

std::vector<float> CosinusPointsGenerator::numbers;

PointsSet* CosinusPointsGenerator::generatePoints()
{
	pointsNumber = 100;
	Vector2D<float>* points = new Vector2D<float>[100];
	float divider = static_cast<float>(pointsNumber);
	float maximumXvalue = 2.0F * PI;
	float additionalFactor = 50.0F;
	float step = (maximumXvalue / divider);

	for (int i = 0; i < pointsNumber; i++)
	{
		float x = i * step;
		float y = cos(x * 4.5F);

		points[i].x = round(x * additionalFactor);
		points[i].y = round(y * additionalFactor);
	}


	PointsSet* pointsSet = new PointsSet();
	pointsSet->points = points;
	pointsSet->pointsNumber = pointsNumber;

	return pointsSet;
}