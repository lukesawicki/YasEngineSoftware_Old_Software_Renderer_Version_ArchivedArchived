#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include<cmath>

template <typename Type>
class Vector2D
{
	public:
		Type x;
		Type y;

		Vector2D()
		{
			this->x = 0;
			this->y = 0;
		}
		Vector2D(Type x, Type y)
		{
			this->x = x;
			this->y = y;
		}
		
		static void normalizedVector(Vector2D<Type>& vector)
		{
			double magnitude = getVectorMagnitude(vector);
			double x = vector.x / magnitude;
			double y = vector.y / magnitude;
			vector.x = static_cast<Type>(x);
			vector.y = static_cast<Type>(y);
		}

		static Type getVectorMagnitude(const Vector2D<Type>& vector)
		{
			return static_cast<Type>(sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0)));
		}

		static Type getVectorMagnitude(Type x0, Type y0, Type x1, Type y1)
		{
			return static_cast<Type>(sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0)));
		}

		static Type crossProduct(const Vector2D<Type>& u, const Vector2D& v)
		{
			return u.x * v.y - u.y * v.x;
		}

		static Type dotProduct(const Vector2D<Type>& u, const Vector2D& v)
		{
			return u.x * v.x + u.y * v.y;
		}

		static Type angleBetweenVectors(const Vector2D<Type>& u, const Vector2D& v)
		{
			return atan2(crossProduct(u, v), dotProduct(u, v));
		}

		static void rotateVectorOverTheAngle(Vector2D<Type>* v, float angle)
		{
			float modifiedX = v->x * cos(angle) - v->y * sin(angle);
			float modifiedY = v->x * sin(angle) + v->y * cos(angle);

			v->x = modifiedX;
			v->y = modifiedY;
		}
		
		static Vector2D<Type> createUnitVectorFromBoundVector(const Vector2D<Type>& u, const Vector2D& v)
		{
			Vector2D<Type> w = Vector2D<Type>(u.x - v.x, u.y - v.y);
			Vector2D::normalizedVector(w);
			return w;
		}

		//minuend => odjemna  - subtrahed => odjemnik
		static void substract(Vector2D<Type>* minued, const Vector2D<Type>& subtrahed)
		{
			minued->x = minued->x - subtrahed.x;
			minued->y = minued->y - subtrahed.y;
		}

		static void multiplyByScalar(Vector2D<Type>* v, Type scalar)
		{
			v->x = v->x * scalar;
			v->y = v->y * scalar;
		}
};

#endif
