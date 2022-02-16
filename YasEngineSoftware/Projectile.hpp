#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include"YasPolygon.hpp"
#include"YasGraphicsLibrary.hpp"

class Projectile : public YasPolygon
{
	public:
		YasVector2D<float> velocity;
		Projectile(float radius, float x, float y, YasVector2D<float> direction);
		~Projectile();
		void move(double deltaTime) override;
		void generate() override;
		void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;
};

#endif
