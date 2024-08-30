#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix4D
{

	public:
		float me00 = 1.0F, me01 = 0.0F, me02 = 0.0F, me03 = 0.0F;
		float me10 = 0.0F, me11 = 1.0F, me12 = 0.0F, me13 = 0.0F;
		float me20 = 0.0F, me21 = 0.0F, me22 = 1.0F, me23 = 0.0F;
		float me30 = 0.0F, me31 = 0.0F, me32 = 0.0F, me33 = 1.0F;

		static Matrix4D multiply(const Matrix4D& a, const Matrix4D& b)
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

		static void identity(Matrix4D& matrix)
		{
			matrix.me00 = 1.0F; matrix.me01 = 0.0F; matrix.me02 = 0.0F; matrix.me03 = 0.0F;
			matrix.me10 = 0.0F; matrix.me11 = 1.0F; matrix.me12 = 0.0F; matrix.me13 = 0.0F;
			matrix.me20 = 0.0F; matrix.me21 = 0.0F; matrix.me22 = 1.0F; matrix.me23 = 0.0F;
			matrix.me30 = 0.0F; matrix.me31 = 0.0F; matrix.me32 = 0.0F; matrix.me33 = 1.0F;
		}
	};

#endif