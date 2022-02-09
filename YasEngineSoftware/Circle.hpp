#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include"Polygon.hpp"
#include"YasGraphicsLibrary.hpp"

namespace YasGL
{
	class Circle : public Polygon
	{
		public:
			Circle(float radius, float x, float y);
			~Circle();
			void move(float deltaTime) override;
			void generate() override;
			void generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
			void regeneratePolygon() override;
	};

}

#endif
