#ifndef LIBMATH_MATRIX_MATRIX4_H_
#define LIBMATH_MATRIX_MATRIX4_H_

#include "LibMath/Vector/Vector4.h"

namespace LibMath
{
	class Matrix4
	{

	public:
							Matrix4() = default;
		explicit			Matrix4(float diagonal);
							Matrix4(float a00, float a01, float a02, float a03, 
								float a10, float a11, float a12, float a13, 
								float a20, float a21, float a22, float a23, 
								float a30, float a31, float a32, float a33);
							Matrix4(Matrix4& other);
							~Matrix4() = default;

		Matrix4&			operator=(Matrix4 const& other);

		class RowProxy {
		private:
			float* row;

		public:

			RowProxy(float* rowRef) {
				row =  rowRef;
			}

			float& operator[](size_t col) {

				if (col > 3)
				{
					throw(std::out_of_range("Error: column out of range"));
				}

				return row[col];
			}
		};

		RowProxy			operator[](size_t row) const;					// alternative for operator[][] overload
		RowProxy			operator[](size_t row);

		Matrix4				transpose(void) const;
		float				determinant(void) const;
		Matrix4				minors(void) const;
		Matrix4				cofators(void) const;
		Matrix4				adjugate(void) const;
		Matrix4				inverse(void) const;

		Matrix4				perspective(float fov, float aspectRatio, float near, float far);

		static		Matrix4			createTransform(LibMath::Vector3 translate = LibMath::Vector3(0.0f, 0.0f, 0.0f), // returns T . R . S
												LibMath::Radian rotation = LibMath::Radian(0.0f),
												LibMath::Vector3 scale = LibMath::Vector3(1.0f, 1.0f, 1.0f),
												LibMath::Vector3 axis = LibMath::Vector3(1.0f, 1.0f, 1.0f));

		static		Matrix4			createTranslate(LibMath::Vector3 translate);
		static		Matrix4			createRotationX(LibMath::Radian angle);
		static		Matrix4			createRotationY(LibMath::Radian angle);
		static		Matrix4			createRotationZ(LibMath::Radian angle);

		static		Matrix4			createScale(LibMath::Vector3 scale);

		static		Matrix4			identity(void);



	private:
		float m_elements[4][4] = { 0.0f };
	};

	Matrix4					operator+(Matrix4 mat1, Matrix4 mat2);
	Matrix4					operator*(Matrix4 mat, float val);
	//LibMath::Vector4		operator*(Matrix4 mat, LibMath::Vector4 vec);
	Matrix4				operator*(Matrix4 mat1, Matrix4 mat2);
}



#endif // !LIBMATH_MATRIX_MATRIX4_H_
