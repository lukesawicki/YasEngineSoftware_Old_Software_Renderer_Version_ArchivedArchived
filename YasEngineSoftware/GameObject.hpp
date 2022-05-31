#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include<cmath>
#include<SDL.h>
#include"Vector2D.hpp"
#include"Vector4D.hpp"

class GameObject
{
	public:
		int lifes = 1;
		Vector2D<float>* localVertices = nullptr;
		Vector2D<float>* worldVertices = nullptr;
		Vector2D<float> vectorZero;
		Vector2D<float> direction;
		Vector4D<Uint8> color;
		Vector2D<float> position;
		int numberOfVertices;
		float rotationSpeed;
		float circumscribedCircleRadius;
		float angleForGenerateInIsoscelesPolygons;
		float startAngle = 0.0F;
		float stepAngle;
		float directionMouseAngle = 0;
		float  speed = 0.0F;
		int layer;

		int iAm;

		virtual void generate() = 0;
		virtual void generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) = 0;
		virtual void regeneratePolygon() = 0;
		  
		virtual void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		virtual void setPosition(const Vector2D<float>& position)
		{
			this->position.x = position.x;
			this->position.y = position.y;
		}
		
		virtual void move(float deltaTime) = 0;

		virtual void setColor(const Vector4D<Uint8>& color)
		{
			this->color.x = color.x;
			this->color.y = color.y;
			this->color.z = color.z;
			this->color.w = color.w;
		}

		virtual virtual int whoAmI()
		{
			return iAm;
		}

		virtual virtual void setMeDead()
		{
			lifes = 0;
		}
	
		

	private:

};

#endif
