#ifndef POLYGON_HPP
#define POLYGON_HPP
#include<cmath>
#include<SDL.h>
#include"YasVector2D.hpp"
#include"YasVector4D.hpp"

class YasPolygon
{
	public:
		YasVector2D<float>* localVertices = nullptr;
		YasVector2D<float>* worldVertices = nullptr;
		YasVector2D<float> vectorZero;
		YasVector2D<float> direction;
		YasVector4D<Uint8> color;
		int numberOfVertices;
		float rotationSpeed;
		float circumscribedCircleRadius;
		float angleForGenerateInIsoscelesPolygons;
		float startAngle = 0.0F;
		float stepAngle;
		float directionMouseAngle = 0;
		float  speed = 0.0F;

		virtual void generate() = 0;
		virtual void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) = 0;
		virtual void regeneratePolygon() = 0;

		virtual void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		virtual void setPosition(const YasVector2D<float>& position)
		{
			this->position.x = position.x;
			this->position.y = position.y;
		}
		
		virtual void move(float deltaTime) = 0;

		virtual void setColor(const YasVector4D<Uint8>& color)
		{
			this->color.x = color.x;
			this->color.y = color.y;
			this->color.z = color.z;
			this->color.w = color.w;
		}

	protected:
		YasVector2D<float> position;

	private:

};

#endif
