#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include"YasGraphicsLibrary.hpp"
#include"YasPolygon.hpp"


class Projectile : public YasPolygon
{
	private:
		bool directionSwitched = false;
	public:
		YasVector2D<float> velocity;
		Projectile(float radius, float x, float y, YasVector2D<float> direction);
		~Projectile();
		void move(float deltaTime) override;
		void generate() override;
		void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;

};

#endif
