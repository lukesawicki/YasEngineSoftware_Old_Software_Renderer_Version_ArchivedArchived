#include"SinusPointsGenerator.hpp"


Vector2D<float>* SinusPointsGenerator::generatePoints()
{
	constexpr int POINTS_NUMBER = 100;
	Vector2D<float>* points = new Vector2D<float>[POINTS_NUMBER];
	constexpr float divider = static_cast<int>(POINTS_NUMBER);
	constexpr float MAX = 2.0F * PI;
	constexpr float additionalFactor = 55.0F;
	float step = (MAX / divider);

	for(int i=0; i<POINTS_NUMBER; i++)
	{
		float x = i * step;
		float y = sin(x);

		points[i].x = x * additionalFactor; // round(x * additionalFactor);
		points[i].y = y * additionalFactor; // round(y * additionalFactor);
	}

	return points;
}
