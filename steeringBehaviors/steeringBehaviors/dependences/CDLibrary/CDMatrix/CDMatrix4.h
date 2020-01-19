#pragma once
#include <math.h>
#include <iostream>
#include <iomanip>
#include <CDVectors/CDVector4.h>
#include <CDMatrix/CDMatrix3.h>
namespace CD
{
	const float DEG2RAD = 3.141593f / 180;

	class CDMatrix4
	{
	public:
		// constructors
		CDMatrix4();  // init with identity
		CDMatrix4(const float src[16]);
		CDMatrix4(float m0, float m1, float m2, float m3, // 1st column
			float m4, float m5, float m6, float m7, // 2nd column
			float m8, float m9, float m10, float m11, // 3rd column
			float m12, float m13, float m14, float m15);// 4th column
		CDMatrix4(CDVector3 m012,float m3,
			CDVector3 m456, float m7, 
			CDVector3 m8910, float m11, 
			CDVector3 m121314, float m15 );
		CDMatrix4(CDVector4 m0123,
			CDVector4 m4567, 
			CDVector4 m891011, 
			CDVector4 m12131415 );

		CDMatrix4 get() const;
		CDMatrix4 getTranspose();                        // return transposed matrix
		float        getDeterminant();

		CDMatrix4&    identity();
		CDMatrix4&    transpose();                            // transpose itself and return reference
		CDMatrix4&    invert();                               // check best inverse method before inverse

		// transform matrix
		CDMatrix4&    translate(float x, float y, float z);   // translation by (x,y,z)
		CDMatrix4&    translate(const CDVector3& vec);            //
		CDMatrix4&    rotate(float angle, const CDVector3& axis); // rotate angle(degree) along the given axix
		CDMatrix4&    rotate(float angle, float x, float y, float z);
		CDMatrix4&    rotateX(float angle);                   // rotate on X-axis with degree
		CDMatrix4&    rotateXstayPos(float angle);                   // rotate on X-axis with degree
		CDMatrix4&    rotateY(float angle);                   // rotate on Y-axis with degree
		CDMatrix4&    rotateYstayPos(float angle);                   // rotate on Y-axis with degree
		CDMatrix4&    rotateZ(float angle);                   // rotate on Z-axis with degree
		CDMatrix4&    rotateZstayPos(float angle);                   // rotate on Z-axis with degree
		CDMatrix4&    scale(float scale);                     // uniform scale
		CDMatrix4&    scale(float sx, float sy, float sz);    // scale by (sx, sy, sz) on each axis
		//
		//// operators
		CDMatrix4     operator+(const CDMatrix4& mat) const;    // add rhs
		CDMatrix4     operator-(const CDMatrix4& mat) const;    // subtract rhs
		CDMatrix4&    operator+=(const CDMatrix4& mat);         // add rhs and update this object
		CDMatrix4&    operator-=(const CDMatrix4& mat);         // subtract rhs and update this object
		CDVector4     operator*(const CDVector4& vec) const;    // multiplication: v' = M * v
		CDVector3     operator*(const CDVector3& vec) const;    // multiplication: v' = M * v
		CDMatrix4     operator*(const CDMatrix4& mat) const;    // multiplication: M3 = M1 * M2
		CDMatrix4&    operator*=(const CDMatrix4& mat);         // multiplication: M1' = M1 * M2
		bool        operator==(const CDMatrix4& mat) const;   // exact compare, no epsilon
		bool        operator!=(const CDMatrix4& mat) const;   // exact compare, no epsilon
		float       operator[](int index) const;            // subscript operator v[0], v[1]
		float&      operator[](int index);                  // subscript operator v[0], v[1]
		//
		friend CDMatrix4 operator-(const CDMatrix4& mat);                     // unary operator (-)
		friend CDMatrix4 operator*(float scalar, const CDMatrix4& mat);       // pre-multiplication
		friend CDVector3 operator*(const CDVector3& vec, const CDMatrix4& mat); // pre-multiplication
		friend CDVector4 operator*(const CDVector4& vec, const CDMatrix4& mat); // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const CDMatrix4& m);

	protected:

	private:
		//float       getCofactor(float m0, float m1, float m2,
		//	float m3, float m4, float m5,
		//	float m6, float m7, float m8);
	public:
		union
		{
			struct
			{
				float m[16];
			};
			struct
			{
				float m_00, m_01, m_02, m_03,
					m_10, m_11, m_12, m_13,
					m_20, m_21, m_22, m_23,
					m_30, m_31, m_32, m_33;
			};
			float M[4][4];
		};                                     // transpose m
	};
	extern  CDMatrix4	transposeMatrix(const CDMatrix4& mat);
	extern  CDMatrix4	invertMatrix(const CDMatrix4& mat);
	extern  CDMatrix4	identityMatrix();
	extern  CDMatrix4   matrix4Translate(float x, float y, float z);			// translation by (x,y,z)
	extern  CDMatrix4   matrix4Translate(const CDVector3& vec);					//
	extern  CDMatrix4   matrix4Rotate(float angle, const CDVector3& axis);		// rotate angle(degree) along the given axix
	extern  CDMatrix4   matrix4Rotate(float angle, float x, float y, float z);
	extern  CDMatrix4   matrix4RotateX(float angle);							// rotate on X-axis with degree
	extern  CDMatrix4   matrix4RotateY(float angle);							// rotate on Y-axis with degree
	extern  CDMatrix4   matrix4RotateZ(float angle);							// rotate on Z-axis with degree
	extern  CDMatrix4   matrix4Scale(float scale);								// uniform scale
	extern  CDMatrix4   matrix4Scale(float sx, float sy, float sz);				// scale by (sx, sy, sz) on each axis
	
}