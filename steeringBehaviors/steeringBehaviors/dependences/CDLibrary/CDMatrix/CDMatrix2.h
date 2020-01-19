#pragma once
#include <math.h>
#include <iostream>
#include <iomanip>
#include <CDVectors/CDVector2.h>
namespace CD
{
	class CDMatrix2
	{
	public:
		// constructors
		CDMatrix2();  // init with identity
		CDMatrix2(const float src[4]);
		CDMatrix2(float m0, float m1, float m2, float m3);
		CDMatrix2(const CDVector2& m0m1, float m2, float m3);
		CDMatrix2(float m0, float m1, const CDVector2& m2m3);
		CDMatrix2(const CDVector2& m0m1, const CDVector2& m2m3);

		//void set(const float src[4]);
		//void set(float m0, float m1, float m2, float m3);
		//void set(const CDVector2& m0m1, float m2, float m3);
		//void set(float m0, float m1, const CDVector2& m2m3);
		//void set(const CDVector2& m0m1, const CDVector2& m2m3);
		//void setRow(int index, const float& row0, const float& row1);
		//void setRow(int index, const float row[2]);
		//void setRow(int index, const CDVector2& vec);
		//void setColumn(int index, const float& col0, const float& col1);
		//void setColumn(int index, const float col[2]);
		//void setColumn(int index, const CDVector2& vec);

		const float* get() const;
		float getDeterminant();

		CDMatrix2& identity();
		CDMatrix2& transpose();                            // transpose itself and return reference
		CDMatrix2 getTranspose();                            // transpose itself and return reference
		CDMatrix2& invert();
		CDMatrix2 getInvert();

		// operators
		CDMatrix2     operator+(const CDMatrix2& mat) const;    // add matrix
		CDMatrix2     operator-(const CDMatrix2& mat) const;    // subtract matrix
		CDMatrix2&    operator+=(const CDMatrix2& mat);         // add rhs and update this object
		CDMatrix2&    operator-=(const CDMatrix2& mat);         // subtract rhs and update this object
		CDVector2     operator*(const CDVector2& vec) const;    // multiplication: v' = M * v
		CDMatrix2     operator*(const CDMatrix2& mat) const;    // multiplication: M3 = M1 * M2
		CDMatrix2&    operator*=(const CDMatrix2& mat);         // multiplication: M1' = M1 * M2
		bool        operator==(const CDMatrix2& mat) const;   // exact compare, no epsilon
		bool        operator!=(const CDMatrix2& mat) const;   // exact compare, no epsilon
		float       operator[](int index) const;            // subscript operator v[0], v[1]
		float&      operator[](int index);                  // subscript operator v[0], v[1]
		CDMatrix2&    operator=(const CDMatrix2& mat);         // multiplication: M1' = M1 * M2

		friend CDMatrix2 operator-(const CDMatrix2& mat);                     // unary operator (-)
		friend CDMatrix2 operator*(float scalar, const CDMatrix2& mat);       // pre-multiplication
		friend CDVector2 operator*(const CDVector2& vec, const CDMatrix2& mat); // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const CDMatrix2& m);

	protected:
	private:
		const float DEG2RAD = 3.141593f / 180;
		const float EPSILON = 0.00001f;
	public:
		union
		{
			struct
			{
				float m[4];
			};
			struct
			{
				float m_11,m_12,m_21,m_22;
			};
			float M[2][2];
		};

	};
	extern CDMatrix2 transposeMatrix(const CDMatrix2& mat);                            // transpose itself and return reference
	extern CDMatrix2 invertMatrix(const CDMatrix2& mat);


}