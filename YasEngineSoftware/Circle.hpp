#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include"YasPolygon.hpp"
#include"YasGraphicsLibrary.hpp"

class Circle : public YasPolygon
{
	private:
		bool directionSwitched;
	public:
		Circle(float radius, float x, float y);
		~Circle();
		void move(float deltaTime) override;
		void generate() override;
		void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;

};

#endif
