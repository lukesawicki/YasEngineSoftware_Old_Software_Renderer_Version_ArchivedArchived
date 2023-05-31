#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include<SDL2/SDL.h>

#include"Collider.hpp"
#include"Vector2D.hpp"
#include"Vector4D.hpp"

class GameObject
{
	public:
		//vXXXXXirtual ~GameObject() = 0;

		enum WhoAmI { DEFAULT_VALUE, PROTAGONIST, PROJECTILE, COLLECTIBLE, GUI_ELEMENT };

		WhoAmI iAm;
		bool isAlive = true;
		Collider collider;
		Vector2D<float>* localVertices = nullptr;
		Vector2D<float>* worldVertices = nullptr;
		Vector2D<float> vectorZero;
		Vector2D<float> direction;
		Vector4D<Uint8> color;
		int numberOfVertices;
		float rotationSpeed;
		float circumscribedCircleRadius;
		float angleForGenerateInIsoscelesPolygons;
		float startAngle = 0.0F;
		float stepAngle;
		float directionMouseAngle = 0;
		float speed = 0.0F;

		virtual void generate() = 0;
		virtual void generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices) = 0;
		virtual void regeneratePolygon() = 0;
		  
		virtual void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
            moveCollider();
		}

        virtual void setX(float x)
        {
            position.x = x;
            moveCollider();
        }

        virtual void setY(float y)
        {
            position.y = y;
            moveCollider();
        }

        virtual Vector2D<float> getPosition()
        {
            return position;
        }


		virtual void setPosition(const Vector2D<float>& position)
		{
			this->position.x = position.x;
			this->position.y = position.y;
            moveCollider();
		}
		
		virtual void move(float deltaTime) = 0;

		virtual void moveCollider()
		{
			collider.x = position.x;
			collider.y = position.y;
		}

		virtual void setColor(const Vector4D<Uint8>& color)
		{
			this->color.x = color.x;
			this->color.y = color.y;
			this->color.z = color.z;
			this->color.w = color.w;
		}

	protected:
		Vector2D<float> position;

	private:

};

#endif
