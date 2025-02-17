#ifndef LIBMATH_MATRIX_MATRIX3_H_
#define LIBMATH_MATRIX_MATRIX3_H_

#include "LibMath/Vector/Vector3.h"

namespace LibMath
{
	class Matrix3Dx3
	{
	public:
							Matrix3Dx3() = default;
		explicit			Matrix3Dx3(float diagonal);
							Matrix3Dx3(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);
							Matrix3Dx3(Matrix3Dx3& other);
							~Matrix3Dx3() = default;

		Matrix3Dx3&			operator=(Matrix3Dx3 const& other);

		class RowProxy {
		private:
			float* row;

		public:
			RowProxy(float* rowRef) {
				/*row[0] = rowRef[0];
				row[1] = rowRef[1];
				row[2] = rowRef[2];*/
				row = rowRef;
			}

			float& operator[](size_t col) {

				if (col > 2)
				{
					throw(std::out_of_range("Error: column out of range"));
				}

				return row[col];
			}
		};

		RowProxy			operator[](size_t row);					// alternative for operator[][] overload

		Matrix3Dx3			transpose(void) const;
		float				determinant(void) const;
		Matrix3Dx3			minors(void) const;
		Matrix3Dx3			cofators(void) const;
		Matrix3Dx3			adjugate(void) const;
		Matrix3Dx3			inverse(void) const;

		static Matrix3Dx3			createTransform(LibMath::Vector2 translate = LibMath::Vector2(0.0f, 0.0f), // returns T . R . S
			LibMath::Radian rotation = LibMath::Radian(0.0f),
			LibMath::Vector2 scale = LibMath::Vector2(1.0f, 1.0f));
	
		static Matrix3Dx3			createRotationX(LibMath::Radian angle);
		static Matrix3Dx3			createRotationY(LibMath::Radian angle);
		static Matrix3Dx3			createRotationZ(LibMath::Radian angle);

		static Matrix3Dx3			createScale(LibMath::Vector3 scale);

		static Matrix3Dx3			identity(void);



	private:
		float m_elements[3][3] = { 0.0f }; // row major matrix

	};
	Matrix3Dx3				operator+(Matrix3Dx3 mat1, Matrix3Dx3 mat2);
	Matrix3Dx3				operator*(Matrix3Dx3 mat, float val);
	LibMath::Vector3		operator*(Matrix3Dx3 mat, LibMath::Vector3 vec);
	Matrix3Dx3				operator*(Matrix3Dx3 mat1, Matrix3Dx3 mat2);
}

#endif // !LIBMATH_MATRIX_MATRIX3_H_
