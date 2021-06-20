#ifndef VECTOR4D_HPP
#define VECTOR4D_HPP

template <typename Type>
class Vector4D
{

public:
	Type x;
	Type y;
	Type z;
	Type w;

	Vector4D()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}
	Vector4D(Type x, Type y, Type z, Type w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

private:

};

#endif
