#ifndef POLYGON_HPP
#define POLYGON_HPP
#include<cmath>
#include<SDL.h>
#include "YasVector2D.hpp"
#include "YasVector4D.hpp"


class YasPolygon
{
	public:
		YasVector2D<float> position;
		YasVector2D<float>* worldVertices = nullptr;
		YasVector2D<float>* localVertices = nullptr;
		YasVector2D<float> direction;
		YasVector2D<float> vectorZero;
		int numberOfVertices = 0;
		YasVector4D<Uint8> color;
		float circumscribedCircleRadius;
		float rotationSpeed;
		float angleForGenerateInIsoscelesPolygons;
		float startAngle = 0.0F;
		float stepAngle;
		float directionMouseAngle = 0; //  90.0 * (3.141592 / 180.0);

		bool directionSwitched = false;
		float  speed = 0.0F;

		virtual void move(float deltaTime) = 0;
		virtual void generate() = 0;
		virtual void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) = 0;
		virtual void regeneratePolygon() = 0;

		virtual void setColor(const YasVector4D<Uint8>& color)
		{
			this->color.x = color.x;
			this->color.y = color.y;
			this->color.z = color.z;
			this->color.w = color.w;
		}
};

#endif
