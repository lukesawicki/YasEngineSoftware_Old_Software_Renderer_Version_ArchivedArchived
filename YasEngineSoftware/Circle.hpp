#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include"Polygonn.hpp"
#include"YasGraphicsLibrary.hpp"

namespace YasGL
{
	class Circle : public Polygonn
	{
		public:
			Circle(int radius, int x, int y);
			void move(double deltaTime) override;
			void generate() override;
			void generateRegularPolygonVertices(Vector2D<int>& position, int circumscribedCircleRadius, int numberOfVertices) override;
	};

}

#endif
