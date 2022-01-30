#ifndef POLYGONN_HPP
#define POLYGONN_HPP
#include "Vector2D.hpp"
#include "Vector4D.hpp"
#include <GLFW/glfw3.h>

namespace YasGL
{

	class Polygonn
	{
		public:
			Vector2D<int> position;
			Vector2D<int>* vertices = nullptr;
			int numberOfVertices = 0;
			int* points = nullptr;
			Vector4D<uint8_t> color;
			int circumscribedCircleRadius;
			float angle;
			float startAngle;
			float stepAngle;

			bool directionSwitched = false;
			int  speedFactor = 255;
			int  speed = 2 * speedFactor;

			virtual void move(double deltaTime) = 0;
			virtual void generate() = 0;
			virtual void generateRegularPolygonVertices(Vector2D<int>& position, int circumscribedCircleRadius, int numberOfVertices) = 0;
	};

}

#endif
