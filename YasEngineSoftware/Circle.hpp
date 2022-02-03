#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include"Polygon.hpp"
#include"YasGraphicsLibrary.hpp"

namespace YasGL
{
	class Circle : public Polygon
	{
		public:
			Circle(int radius, int x, int y);
			~Circle();
			void move(double deltaTime) override;
			void generate() override;
			void generateRegularPolygonVertices(const Vector2D<int>& position, int circumscribedCircleRadius, int numberOfVertices) override;
			void regeneratePolygon() override;
	};

}

#endif
