#ifndef MATRIX_4_4_HPP
#define MATRIX_4_4_HPP

// element_*_*_ - are named elements or entries wedlug
// wedlug Ilustrowanego slownika matematycznego element

class Matrix_4_4
{
	public:
		float element_0_0_ = 0.0F, element_0_1_ = 0.0F, element_0_2_ = 0.0F, element_0_3_ = 0.0F;
		float element_1_0_ = 0.0F, element_1_1_ = 0.0F, element_1_2_ = 0.0F, element_1_3_ = 0.0F;
		float element_2_0_ = 0.0F, element_2_1_ = 0.0F, element_2_2_ = 0.0F, element_2_3_ = 0.0F;
		float element_3_0_ = 0.0F, element_3_1_ = 0.0F, element_3_2_ = 0.0F, element_3_3_ = 0.0F;

		static Matrix_4_4 Multiply(const Matrix_4_4& matrix_0, const Matrix_4_4& matrix_1)
		{
			Matrix_4_4 matrix_4d =
			{
				matrix_0.element_0_0_ * matrix_1.element_0_0_ + matrix_0.element_0_1_ * matrix_1.element_1_0_ + matrix_0.element_0_2_ * matrix_1.element_2_0_ + matrix_0.element_0_3_ * matrix_1.element_3_0_, /*|*/ matrix_0.element_0_0_ * matrix_1.element_0_1_ + matrix_0.element_0_1_ * matrix_1.element_1_1_ + matrix_0.element_0_2_ * matrix_1.element_2_1_ + matrix_0.element_0_3_ * matrix_1.element_3_1_, /*|*/ matrix_0.element_0_0_ * matrix_1.element_0_2_ + matrix_0.element_0_1_ * matrix_1.element_1_2_ + matrix_0.element_0_2_ * matrix_1.element_2_2_ + matrix_0.element_0_3_ * matrix_1.element_3_2_, /*|*/ matrix_0.element_0_0_ * matrix_1.element_0_3_ + matrix_0.element_0_1_ * matrix_1.element_1_3_ + matrix_0.element_0_2_ * matrix_1.element_2_3_ + matrix_0.element_0_3_ * matrix_1.element_3_3_,
				matrix_0.element_1_0_ * matrix_1.element_0_0_ + matrix_0.element_1_1_ * matrix_1.element_1_0_ + matrix_0.element_1_2_ * matrix_1.element_2_0_ + matrix_0.element_1_3_ * matrix_1.element_3_0_, /*|*/ matrix_0.element_1_0_ * matrix_1.element_0_1_ + matrix_0.element_1_1_ * matrix_1.element_1_1_ + matrix_0.element_1_2_ * matrix_1.element_2_1_ + matrix_0.element_1_3_ * matrix_1.element_3_1_, /*|*/ matrix_0.element_1_0_ * matrix_1.element_0_2_ + matrix_0.element_1_1_ * matrix_1.element_1_2_ + matrix_0.element_1_2_ * matrix_1.element_2_2_ + matrix_0.element_1_3_ * matrix_1.element_3_2_, /*|*/ matrix_0.element_1_0_ * matrix_1.element_0_3_ + matrix_0.element_1_1_ * matrix_1.element_1_3_ + matrix_0.element_1_2_ * matrix_1.element_2_3_ + matrix_0.element_1_3_ * matrix_1.element_3_3_,
				matrix_0.element_2_0_ * matrix_1.element_0_0_ + matrix_0.element_2_1_ * matrix_1.element_1_0_ + matrix_0.element_2_2_ * matrix_1.element_2_0_ + matrix_0.element_2_3_ * matrix_1.element_3_0_, /*|*/ matrix_0.element_2_0_ * matrix_1.element_0_1_ + matrix_0.element_2_1_ * matrix_1.element_1_1_ + matrix_0.element_2_2_ * matrix_1.element_2_1_ + matrix_0.element_2_3_ * matrix_1.element_3_1_, /*|*/ matrix_0.element_2_0_ * matrix_1.element_0_2_ + matrix_0.element_2_1_ * matrix_1.element_1_2_ + matrix_0.element_2_2_ * matrix_1.element_2_2_ + matrix_0.element_2_3_ * matrix_1.element_3_2_, /*|*/ matrix_0.element_2_0_ * matrix_1.element_0_3_ + matrix_0.element_2_1_ * matrix_1.element_1_3_ + matrix_0.element_2_2_ * matrix_1.element_2_3_ + matrix_0.element_2_3_ * matrix_1.element_3_3_,
				matrix_0.element_3_0_ * matrix_1.element_0_0_ + matrix_0.element_3_1_ * matrix_1.element_1_0_ + matrix_0.element_3_2_ * matrix_1.element_2_0_ + matrix_0.element_3_3_ * matrix_1.element_3_0_, /*|*/ matrix_0.element_3_0_ * matrix_1.element_0_1_ + matrix_0.element_3_1_ * matrix_1.element_1_1_ + matrix_0.element_3_2_ * matrix_1.element_2_1_ + matrix_0.element_3_3_ * matrix_1.element_3_1_, /*|*/ matrix_0.element_3_0_ * matrix_1.element_0_2_ + matrix_0.element_3_1_ * matrix_1.element_1_2_ + matrix_0.element_3_2_ * matrix_1.element_2_2_ + matrix_0.element_3_3_ * matrix_1.element_3_2_, /*|*/ matrix_0.element_3_0_ * matrix_1.element_0_3_ + matrix_0.element_3_1_ * matrix_1.element_1_3_ + matrix_0.element_3_2_ * matrix_1.element_2_3_ + matrix_0.element_3_3_ * matrix_1.element_3_3_
			};
			return matrix_4d;
		}

		static void ClearOutMatrix(Matrix_4_4& matrix)
		{
			matrix.element_0_0_ = 0.0F; matrix.element_0_1_ = 0.0F; matrix.element_0_2_ = 0.0F; matrix.element_0_3_ = 0.0F;
			matrix.element_1_0_ = 0.0F; matrix.element_1_1_ = 0.0F; matrix.element_1_2_ = 0.0F; matrix.element_1_3_ = 0.0F;
			matrix.element_2_0_ = 0.0F; matrix.element_2_1_ = 0.0F; matrix.element_2_2_ = 0.0F; matrix.element_2_3_ = 0.0F;
			matrix.element_3_0_ = 0.0F; matrix.element_3_1_ = 0.0F; matrix.element_3_2_ = 0.0F; matrix.element_3_3_ = 0.0F;
		}

		static void ChangeMatrixToIdentity(Matrix_4_4& matrix)
		{
			matrix.element_0_0_ = 1.0F; matrix.element_0_1_ = 0.0F; matrix.element_0_2_ = 0.0F; matrix.element_0_3_ = 0.0F;
			matrix.element_1_0_ = 0.0F; matrix.element_1_1_ = 1.0F; matrix.element_1_2_ = 0.0F; matrix.element_1_3_ = 0.0F;
			matrix.element_2_0_ = 0.0F; matrix.element_2_1_ = 0.0F; matrix.element_2_2_ = 1.0F; matrix.element_2_3_ = 0.0F;
			matrix.element_3_0_ = 0.0F; matrix.element_3_1_ = 0.0F; matrix.element_3_2_ = 0.0F; matrix.element_3_3_ = 1.0F;
		}

		static Matrix_4_4* GetTransposedMatrix(const Matrix_4_4* source_matrix)
		{
      Matrix_4_4* destination_matrix = {
            source_matrix.element_0_0_, source_matrix.element_1_0_, source_matrix.element_2_0_,source_matrix.element_3_0_,
            source_matrix.element_0_1_, source_matrix.element_1_1_, source_matrix.element_2_1_, source_matrix.element_3_1_,
            source_matrix.element_0_2_, source_matrix.element_1_2_, source_matrix.element_2_2_, source_matrix.element_3_2_,
            source_matrix.element_0_3_, source_matrix.element_1_3_, source_matrix.element_2_3_, source_matrix.element_3_3_
      };
      return destination_matrix;
    }

    static void TransposeMatrix(Matrix_4_4* matrix)
    {
      matrix->element_0_0_ = matrix->element_0_0_; matrix->element_0_1_ = matrix->element_1_0_; matrix->element_0_2_ = matrix->element_2_0_; matrix->element_0_3_ = matrix->element_3_0_;
      matrix->element_1_0_ = matrix->element_0_1_; matrix->element_1_1_ = matrix->element_1_1_; matrix->element_1_2_ = matrix->element_2_1_; matrix->element_1_3_ = matrix->element_3_1_;
      matrix->element_2_0_ = matrix->element_0_2_; matrix->element_2_1_ = matrix->element_1_2_; matrix->element_2_2_ = matrix->element_2_2_; matrix->element_2_3_ = matrix->element_3_2_;
      matrix->element_3_0_ = matrix->element_0_3_; matrix->element_3_1_ = matrix->element_1_3_; matrix->element_3_2_ = matrix->element_2_3_; matrix->element_3_3_ = matrix->element_3_3_;
    }
	};

#endif
