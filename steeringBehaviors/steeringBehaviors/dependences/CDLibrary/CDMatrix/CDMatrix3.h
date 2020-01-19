#pragma once
#include <math.h>
#include <iostream>
#include <iomanip>
#include <CDVectors/CDVector3.h>

namespace CD
{
	class CDMatrix3
	{
	public:
		// constructors
		CDMatrix3();  // init with identity
		CDMatrix3(const float src[9]);
		CDMatrix3(float m0, float m1, float m2,           // 1st row
			float m3, float m4, float m5,           // 2nd row
			float m6, float m7, float m8);          // 3rd row
		CDMatrix3(const CDVector3& m012,           // 1st row
			const CDVector3& m345,           // 2nd row
			const CDVector3& m678);          // 3rd row
		const float* get() const;
		float       getDeterminant();

		CDMatrix3&    identity();
		CDMatrix3&    transpose();                          // transpose itself and return reference
		CDMatrix3     getTranspose();                       // transpose itself and return reference
		CDMatrix3&    invert();
		CDMatrix3     getInvert();

		CDMatrix3&    translate(float x, float y);			// translation by (x,y)
		CDMatrix3&    translate(const CDVector2& vec);      // translation by (x,y)
		CDMatrix3&    rotate(float angle);                  // rotate on Y-axis with degree}
		CDMatrix3&    scale(float scale);                   // uniform scale
		CDMatrix3&    scale(float sx, float sy);			// scale by (sx, sy, sz) on each axis
		CDMatrix3&    shearX(float lenght);			// scale by (sx, sy, sz) on each axis
		CDMatrix3&    shearY(float lenght);			// scale by (sx, sy, sz) on each axis


		// operators
		CDMatrix3     operator+(const CDMatrix3& mat) const;    // add matrix
		CDMatrix3     operator-(const CDMatrix3& mat) const;    // subtract matrix
		CDMatrix3&    operator+=(const CDMatrix3& mat);         // add rhs and update this object
		CDMatrix3&    operator-=(const CDMatrix3& mat);         // subtract rhs and update this object
		CDVector3     operator*(const CDVector3& vec) const;    // multiplication: v' = M * v
		CDMatrix3     operator*(const CDMatrix3& mat) const;    // multiplication: M3 = M1 * M2
		CDMatrix3&    operator*=(const CDMatrix3& mat);         // multiplication: M1' = M1 * M2
		bool        operator==(const CDMatrix3& mat) const;   // exact compare, no epsilon
		bool        operator!=(const CDMatrix3& mat) const;   // exact compare, no epsilon
		float       operator[](int index) const;            // subscript operator v[0], v[1]
		float&      operator[](int index);                  // subscript operator v[0], v[1]
		
		friend CDMatrix3 operator-(const CDMatrix3& mat);                     // unary operator (-)
		friend CDMatrix3 operator*(float scalar, const CDMatrix3& mat);       // pre-multiplication
		friend CDVector3 operator*(const CDVector3& vec, const CDMatrix3& mat); // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const CDMatrix3& mat);

	protected:

	public:
		union
		{
			struct
			{
				float m[9];
			};
			struct
			{
				float m_00, m_01,m_02, 
					m_10, m_11,m_12,
					m_20,m_21,m_22;
			};
			float M[3][3];
		};

	};
	extern CDMatrix3	matrix3Transpose(const CDMatrix3& mat);
	extern CDMatrix3	matrix3Invert(const CDMatrix3& mat);
	extern CDMatrix3	matrix3Identity();
	extern CDMatrix3    matrix3Translate(float x, float y);			// translation by (x,y)
	extern CDMatrix3    matrix3Translate(const CDVector2& vec);     // translation by (x,y)
	extern CDMatrix3    matrix3Rotate(float angle);                 // rotate on Y-axis with degree}
	extern CDMatrix3    matrix3Scale(float scale);                  // uniform scale
	extern CDMatrix3    matrix3Scale(float sx, float sy);			// scale by (sx, sy, sz) on each axis


}