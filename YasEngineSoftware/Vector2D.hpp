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

};

#endif
