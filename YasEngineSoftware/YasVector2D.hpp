#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include<cmath>

template <typename Type>
class YasVector2D
{
	public:
		Type x;
		Type y;

		YasVector2D()
		{
			this->x = 0;
			this->y = 0;
		}
		YasVector2D(Type x, Type y)
		{
			this->x = x;
			this->y = y;
		}
		
		static void normalizedVector(YasVector2D<Type>& vector)
		{
			double magnitude = getVectorMagnitude(vector);
			double x = vector.x / magnitude;
			double y = vector.y / magnitude;
			vector.x = static_cast<Type>(x);
			vector.y = static_cast<Type>(y);
		}

		static YasVector2D<Type>* normalizedVector(const YasVector2D<Type>& vector)
		{
			double magnitude = getVectorMagnitude(vector);
			double x = vector.x / magnitude;
			double y = vector.y / magnitude;
			vector.x = static_cast<Type>(x);
			vector.y = static_cast<Type>(y);
			return new YasVector2D<Type>(x, y);
		}

		static Type getVectorMagnitude(const YasVector2D<Type>& vector)
		{
			return static_cast<Type>(sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0)));
		}

		static Type getVectorMagnitude(Type x0, Type y0, Type x1, Type y1)
		{
			return static_cast<Type>(sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0)));
		}

		static Type angleBetweenVectors(const YasVector2D<Type>& u, const YasVector2D& v)
		{
			return atan2f
			(
				(u.x * v.x + u.y * v.y),
				(YasVector2D<Type>::getVectorMagnitude(u) * YasVector2D<Type>::getVectorMagnitude(v))
			);
		}

		static void rotateVectorOverTheAngle(YasVector2D<Type>& v, float angle)
		{
			float modifiedX = v.x * cos(angle) - v.y * sin(angle);
			float modifiedY = v.x * sin(angle) + v.y * cos(angle);

			v.x = modifiedX;
			v.y = modifiedX;
		}
};

#endif


/*float x = localVertices[i].x * cos(directionMouseAngle) - localVertices[i].y * sin(directionMouseAngle);
float y = localVertices[i].x * sin(directionMouseAngle) + localVertices[i].y * cos(directionMouseAngle);

localVertices[i].x = x;
localVertices[i].y = y;*/