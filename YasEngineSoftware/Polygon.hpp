#ifndef POLYGON_HPP
#define POLYGON_HPP
#include<cmath>
#include "Vector2D.hpp"
#include "Vector4D.hpp"
#include <GLFW/glfw3.h>

namespace YasGL
{
	class Polygon
	{
		public:
			Vector2D<float> position;
			Vector2D<float>* worldVertices = nullptr;
			Vector2D<float>* localVertices = nullptr;
			int numberOfVertices = 0;
			Vector4D<uint8_t> color;
			float circumscribedCircleRadius;
			float rotationSpeed;
			float angle;
			float startAngle;
			float stepAngle;

			bool directionSwitched = false;
			float  speed = 0.0F;

			virtual void move(float deltaTime) = 0;
			virtual void generate() = 0;
			virtual void generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) = 0;
			virtual void regeneratePolygon() = 0;
			virtual void setColor(const Vector4D<uint8_t>& color)
			{
				this->color.x = color.x;
				this->color.y = color.y;
				this->color.z = color.z;
				this->color.w = color.w;
			}
	};

}

#endif
