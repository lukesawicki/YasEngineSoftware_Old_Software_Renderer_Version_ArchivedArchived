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
		
		static YasVector2D<Type>* getNormalizedVector(YasVector2D<Type>& vector)
		{
			float magnitude = getVectorMagnitude(vector);
			float x = vector.x / magnitude;
			float y = vector.y / magnitude;
			return new YasVector2D<Type>(x, y);
		}

		static Type getVectorMagnitude(const YasVector2D<Type>& vector)
		{
			return sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
		}
};

#endif
