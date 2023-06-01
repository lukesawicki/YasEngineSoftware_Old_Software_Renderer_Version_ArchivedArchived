#include"SinusPointsGenerator.hpp"


PointsSet* SinusPointsGenerator::generatePoints()
{
	pointsNumber = 100;
	Vector2D<float>* points = new Vector2D<float>[pointsNumber];
	float divider = static_cast<float>(pointsNumber);
	float maximumXvalue = 2.0F * PI;
	constexpr float additionalFactor = 55.0F;
	float step = (maximumXvalue / divider);

	for(int i=0; i< pointsNumber; i++)
	{
		float x = i * step;
		float y = sin(x);

		points[i].x = x * additionalFactor; // round(x * additionalFactor);
		points[i].y = y * additionalFactor; // round(y * additionalFactor);
	}

	PointsSet* pointsSet = new PointsSet();
	pointsSet->points = points;
	pointsSet->pointsNumber = pointsNumber;
	return pointsSet;
}
