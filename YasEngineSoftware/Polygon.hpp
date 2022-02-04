#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "Vector2D.hpp"
#include "Vector4D.hpp"
#include <GLFW/glfw3.h>

namespace YasGL
{
	class Polygon
	{
		public:
			Vector2D<int> position;
			Vector2D<int>* vertices = nullptr;
			int numberOfVertices = 0;
			//int* points = nullptr;
			Vector4D<uint8_t> color;
			int circumscribedCircleRadius;
			float angle;
			float startAngle;
			float stepAngle;

			bool directionSwitched = false;
			int  speedFactor = 0;
			int  speed = 200;

			virtual void move(double deltaTime) = 0;
			virtual void generate() = 0;
			virtual void generateRegularPolygonVertices(const Vector2D<int>& position, int circumscribedCircleRadius, int numberOfVertices) = 0;
			virtual void regeneratePolygon() = 0;
	};

}

#endif
