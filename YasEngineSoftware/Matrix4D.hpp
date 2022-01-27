#ifndef MATRIX4D_HPP
#define MATRIX4D_HPP

#include<cmath>
#include"Vector3D.hpp"

class Matrix4D
{
	public:
		float me00 = 1.0F, me01 = 0.0F, me02 = 0.0F, me03 = 0.0F;
		float me10 = 0.0F, me11 = 1.0F, me12 = 0.0F, me13 = 0.0F;
		float me20 = 0.0F, me21 = 0.0F, me22 = 1.0F, me23 = 0.0F;
		float me30 = 0.0F, me31 = 0.0F, me32 = 0.0F, me33 = 1.0F;

	private:

};

#endif