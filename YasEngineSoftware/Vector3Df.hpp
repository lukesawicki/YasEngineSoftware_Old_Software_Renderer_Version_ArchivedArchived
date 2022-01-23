#pragma once
#ifndef VECTOR4D_HPP
#define VECTOR4D_HPP

class Vector3Df
{

public:
	float x;
	float y;
	float z;
	float w;

	Vector3Df()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}
	Vector3Df(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

private:

};

#endif