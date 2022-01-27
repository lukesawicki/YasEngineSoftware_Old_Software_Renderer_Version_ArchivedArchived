#ifndef YASMATHEMATICSLIBRARY_HPP
#define YASMATHEMATICSLIBRARY_HPP
#include<cmath>
#include<iostream>
//#include <GLFW/glfw3.h>
//#include"Vector2D.hpp"
//#include"Vector3D.hpp"
#include"Vector4D.hpp"
#include"Matrix4D.hpp"
//#include "PixelsTable.hpp"


namespace YasMathLib
{
	static Matrix4D multiplyMatrices(const Matrix4D& a, const Matrix4D& b)
	{
		Matrix4D mat =
		{
			a.me00 * b.me00 + a.me01 * b.me10 + a.me02 * b.me20 + a.me03 * b.me30, /*|*/ a.me00 * b.me01 + a.me01 * b.me11 + a.me02 * b.me21 + a.me03 * b.me31, /*|*/ a.me00 * b.me02 + a.me01 * b.me12 + a.me02 * b.me22 + a.me03 * b.me32, /*|*/ a.me00 * b.me03 + a.me01 * b.me13 + a.me02 * b.me23 + a.me03 * b.me33,
			a.me10 * b.me00 + a.me11 * b.me10 + a.me12 * b.me20 + a.me13 * b.me30, /*|*/ a.me10 * b.me01 + a.me11 * b.me11 + a.me12 * b.me21 + a.me13 * b.me31, /*|*/ a.me10 * b.me02 + a.me11 * b.me12 + a.me12 * b.me22 + a.me13 * b.me32, /*|*/ a.me10 * b.me03 + a.me11 * b.me13 + a.me12 * b.me23 + a.me13 * b.me33,
			a.me20 * b.me00 + a.me21 * b.me10 + a.me22 * b.me20 + a.me23 * b.me30, /*|*/ a.me20 * b.me01 + a.me21 * b.me11 + a.me22 * b.me21 + a.me23 * b.me31, /*|*/ a.me20 * b.me02 + a.me21 * b.me12 + a.me22 * b.me22 + a.me23 * b.me32, /*|*/ a.me20 * b.me03 + a.me21 * b.me13 + a.me22 * b.me23 + a.me23 * b.me33,
			a.me30 * b.me00 + a.me31 * b.me10 + a.me32 * b.me20 + a.me33 * b.me30, /*|*/ a.me30 * b.me01 + a.me31 * b.me11 + a.me32 * b.me21 + a.me33 * b.me31, /*|*/ a.me30 * b.me02 + a.me31 * b.me12 + a.me32 * b.me22 + a.me33 * b.me32, /*|*/ a.me30 * b.me03 + a.me31 * b.me13 + a.me32 * b.me23 + a.me33 * b.me33
		};
		return mat;
	}

	static Matrix4D createIdentityMatrix()
	{
		Matrix4D matrix;
		setToIdentityMatrix(matrix);
		return matrix;
	}

	static void setToIdentityMatrix(Matrix4D& matrix)
	{
		matrix.me00 = 1.0F; matrix.me01 = 0.0F; matrix.me02 = 0.0F; matrix.me03 = 0.0F;
		matrix.me10 = 0.0F; matrix.me11 = 1.0F; matrix.me12 = 0.0F; matrix.me13 = 0.0F;
		matrix.me20 = 0.0F; matrix.me21 = 0.0F; matrix.me22 = 1.0F; matrix.me23 = 0.0F;
		matrix.me30 = 0.0F; matrix.me31 = 0.0F; matrix.me32 = 0.0F; matrix.me33 = 1.0F;
	}

	static Matrix4D vectorToTranslationMatrix(const Vector3D<int>& vector)
	{
		Matrix4D mat =
		{
			mat.me00 = 1.0F, mat.me01 = 0.0F, mat.me02 = 0.0F, mat.me03 = 0.0F,
			mat.me10 = 0.0F, mat.me11 = 1.0F, mat.me12 = 0.0F, mat.me13 = 0.0F,
			mat.me20 = 0.0F, mat.me21 = 0.0F, mat.me22 = 1.0F, mat.me23 = 0.0F,
			mat.me30 = vector.x,    mat.me31 = vector.y,    mat.me32 = vector.z,    mat.me33 = 1.0F
		};

		return mat;
	}

	static Matrix4D rotationAroundArbitraryAxies(Vector3D<float> axisVector, const float& angle)
	{
		float c = cos(angle);
		float s = sin(angle);

		Vector3D<float> normalizedAxisVector;

		float vectorMagnitude = sqrt(pow(normalizedAxisVector.x, 2) + pow(normalizedAxisVector.y, 2) + pow(normalizedAxisVector.z, 2));

		normalizedAxisVector.x = normalizedAxisVector.x / vectorMagnitude;
		normalizedAxisVector.y = normalizedAxisVector.y / vectorMagnitude;
		normalizedAxisVector.z = normalizedAxisVector.z / vectorMagnitude;

		Matrix4D mat =
		{
			mat.me00 = c + ((1.0F - c) * normalizedAxisVector.x) * normalizedAxisVector.x,               mat.me01 = ((1.0F - c) * normalizedAxisVector.x) * normalizedAxisVector.y - s * normalizedAxisVector.z, mat.me02 = ((1.0F - c) * normalizedAxisVector.x) * normalizedAxisVector.z + s * normalizedAxisVector.y, mat.me03 = 0.0F,
			mat.me10 = ((1.0F - c) * normalizedAxisVector.y) * normalizedAxisVector.x + s * normalizedAxisVector.z, mat.me11 = c + ((1.0F - c) * normalizedAxisVector.y) * normalizedAxisVector.y,                mat.me12 = ((1.0F - c) * normalizedAxisVector.y) * normalizedAxisVector.z - s * normalizedAxisVector.x, mat.me13 = 0.0F,
			mat.me20 = ((1.0F - c) * normalizedAxisVector.z) * normalizedAxisVector.x - s * normalizedAxisVector.y, mat.me21 = ((1.0F - c) * normalizedAxisVector.z) * normalizedAxisVector.y + s * normalizedAxisVector.x, mat.me22 = c + ((1.0F - c) * normalizedAxisVector.z) * normalizedAxisVector.z,                mat.me23 = 0.0F,
			mat.me30 = 0.0F,                                                        mat.me31 = 0.0F,                                                        mat.me32 = 0.0F,                                                        mat.me33 = 1.0F,
		};

		return mat;
	}

	static Vector4D<float> multiplyMatrixVector(Matrix4D matrix, Vector4D<float> vector)
	{
		Vector4D<float> resultVector;

		resultVector.x = vector.x * matrix.me00 + vector.y * matrix.me01 + vector.z * matrix.me02 + vector.w * matrix.me03;
		resultVector.y = vector.x * matrix.me10 + vector.y * matrix.me11 + vector.z * matrix.me12 + vector.w * matrix.me13;
		resultVector.z = vector.x * matrix.me20 + vector.y * matrix.me21 + vector.z * matrix.me22 + vector.w * matrix.me23;
		resultVector.w = vector.x * matrix.me30 + vector.y * matrix.me31 + vector.z * matrix.me32 + vector.w * matrix.me33;

		return resultVector;
	}
}

#endif