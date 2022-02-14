#ifndef POLYGON_HPP
#define POLYGON_HPP
#include<cmath>
#include "YasVector2D.hpp"
#include "YasVector4D.hpp"
#include <GLFW/glfw3.h>

class YasPolygon
{
	public:
		YasVector2D<float> position;
		YasVector2D<float>* worldVertices = nullptr;
		YasVector2D<float>* localVertices = nullptr;
		int numberOfVertices = 0;
		YasVector4D<uint8_t> color;
		float circumscribedCircleRadius;
		float rotationSpeed;
		float angle;
		float startAngle;
		float stepAngle;

		bool directionSwitched = false;
		float  speed = 0.0F;

		virtual void move(float deltaTime) = 0;
		virtual void generate() = 0;
		virtual void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) = 0;
		virtual void regeneratePolygon() = 0;
		virtual void setColor(const YasVector4D<uint8_t>& color)
		{
			this->color.x = color.x;
			this->color.y = color.y;
			this->color.z = color.z;
			this->color.w = color.w;
		}
};

#endif
