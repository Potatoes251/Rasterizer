#ifndef LIBMATH_MATRIX_MATRIX2_H_
#define LIBMATH_MATRIX_MATRIX2_H_

#include "LibMath/GeometricObject2.h"

namespace LibMath
{
	class Matrix2Dx2
	{
	public:

							Matrix2Dx2() = default;
		explicit			Matrix2Dx2(float diagonal);
							Matrix2Dx2(float a1, float a2, float a3, float a4);
							Matrix2Dx2(Matrix2Dx2& other);
							~Matrix2Dx2() = default;
		

		class RowProxy { 
			private:
				float row[2];

			public:
				RowProxy(float rowRef[2]) {
					row[0] = rowRef[0];
					row[1] = rowRef[1];
				}

				float& operator[](size_t col) {
					if (col > 1)
					{
						throw(std::out_of_range("Error: column out of range"));
					}
					return row[col];
				}
		};

		Matrix2Dx2&			operator=(Matrix2Dx2& other);
		//void				operator=(Matrix2Dx2 other);

		bool				operator==(Matrix2Dx2& other);
		RowProxy			operator[](size_t row);					// alternative for operator[][] overload

		float				determinant(void);
		Matrix2Dx2			minors(void);
		Matrix2Dx2			cofactors(void);
		Matrix2Dx2			adjugate(void);
		Matrix2Dx2			inverse(void);
		Matrix2Dx2			transpose(void);


		Matrix2Dx2			createRotation(Radian const& rad);
		Matrix2Dx2			createScale(LibMath::Vector2 vec);
		Matrix2Dx2			createTransform(LibMath::Radian rad = 0_rad, LibMath::Vector2 scale = Vector2(1, 1));

		Matrix2Dx2			identity(void);
		

	private:
		float m_elements[2][2] = {0};

	};
	Matrix2Dx2			operator+(Matrix2Dx2 m1, Matrix2Dx2 m2);
	Matrix2Dx2			operator*(Matrix2Dx2 m1, Matrix2Dx2 m2);
	Matrix2Dx2			operator*(Matrix2Dx2 m1, float scalair);
	LibMath::Vector2			operator*(Matrix2Dx2 m, LibMath::Vector2 vec);

	class Matrix2Dx3
	{
	public:
		Matrix2Dx3() = default;
		Matrix2Dx3(float diagonal);
		Matrix2Dx3(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);
		Matrix2Dx3(Matrix2Dx3& other);

		Matrix2Dx3& operator=(Matrix2Dx3& other);

		class RowProxy {
		private:
			float row[3];

		public:
			RowProxy(float rowRef[3]) {
				row[0] = rowRef[0];
				row[1] = rowRef[1];
				row[2] = rowRef[2];
			}

			float& operator[](size_t col) {

				if (col >2)
				{
					throw(std::out_of_range("Error: column out of range"));
				}

				return row[col];
			}
		};

		RowProxy	operator[](size_t row);
		bool		operator==(Matrix2Dx3& m);

		Matrix2Dx3	createTranslation(LibMath::Vector2 translation);
		Matrix2Dx3	createRotation(LibMath::Point2 point, LibMath::Radian rad);
		Matrix2Dx3	createScale(LibMath::Vector2 scale);

		Matrix2Dx3	createTransform(LibMath::Vector2 translation = LibMath::Vector2(0, 0), 
			LibMath::Radian rotation = LibMath::Radian(0), LibMath::Vector2 scale = LibMath::Vector2(1, 1));

		Matrix2Dx3	identity(void);
		


		~Matrix2Dx3() = default;
		

	private:
		float m_elements[3][3] = { 0 };

	};
	Matrix2Dx3			operator+(Matrix2Dx3 m1, Matrix2Dx3 m2);
	Matrix2Dx3			operator*(Matrix2Dx3 m, float scalair);
	//Matrix2Dx3			operator*(Matrix2Dx3 m, LibMath::Vector3 vec);
	Matrix2Dx3			operator*(Matrix2Dx3 m1, Matrix2Dx3 m2);
}

#endif // !LIBMATH_MATRIX_MATRIX2_H_