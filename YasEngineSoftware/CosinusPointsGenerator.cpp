#include"CosinusPointsGenerator.hpp"


Vector2D<float>* CosinusPointsGenerator::generatePoints()
{
	constexpr int POINTS_NUMBER = 100;
	Vector2D<float>* points = new Vector2D<float>[100];
	constexpr float divider = static_cast<int>(POINTS_NUMBER);
	constexpr float MAX = 2.0F * PI;
	constexpr float additionalFactor = 50.0F;
	float step = (MAX / divider);

	for (int i = 0; i < POINTS_NUMBER; i++)
	{
		float x = i * step;
		float y = cos(x * 4.5F);

		points[i].x = round(x * additionalFactor);
		points[i].y = round(y * additionalFactor);
	}

	return points;
}