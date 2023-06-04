#include"SinusPointsGenerator.hpp"

std::vector<double> SinusPointsGenerator::numbers; // FOR GAMEPLAY PURPOSE!!

PointsSet* SinusPointsGenerator::generatePoints()
{
	pointsNumber = 100;
	Vector2D<double>* points = new Vector2D<double>[pointsNumber];
	double divider = static_cast<double>(pointsNumber);
	double maximumXvalue = 2.0L * PI;
	constexpr double additionalFactor = 50.0;
	double step = (maximumXvalue / divider);

	for(int i = 0; i < pointsNumber; i++)
	{
		double x = i * step;
		double y = sin(x);
		numbers.push_back(y); // FOR GAMEPLAY PURPOSE!!
		points[i].x = x * additionalFactor; // round(x * additionalFactor);
		points[i].y = y * additionalFactor; // round(y * additionalFactor);
	}

	PointsSet* pointsSet = new PointsSet();
	pointsSet->points = new Vector2D<float>[pointsNumber];
	for(int i = 0; i < pointsNumber; i++)
	{
		pointsSet->points[i].x = static_cast<float>(points[i].x);
		pointsSet->points[i].y = static_cast<float>(points[i].y);
	}
	// pointsSet->points = points;

	pointsSet->pointsNumber = pointsNumber;
	return pointsSet;
}
