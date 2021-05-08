#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

template <typename Type>
class Vector3D
{

    public:
        Type x;
        Type y;
        Type z;

        Vector3D()
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }
        Vector3D(Type x, Type y, Type z)
        {
            this->x = x;
            this->y = y;
            this->z = y;
        }
    private:

};

#endif
