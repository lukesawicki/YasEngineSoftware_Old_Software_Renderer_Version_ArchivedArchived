#ifndef VECTOR4D_HPP
#define VECTOR4D_HPP

template <typename Type>
class YasVector4D
{
	public:
		Type x;
		Type y;
		Type z;
		Type w;

		YasVector4D()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 0;
		}

		YasVector4D(Type x, Type y, Type z, Type w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
};

#endif
