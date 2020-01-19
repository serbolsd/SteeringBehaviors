#include <CDMatrix/CDMatrix4.h>
namespace CD
{
	 CD::CDMatrix4::CDMatrix4()
	{
		m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
		m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
		m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
		m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
	}

	 CD::CDMatrix4::CDMatrix4(const float src[16])
	{
		m[0] = src[0];   m[1] = src[1];  m[2] = src[2];   m[3] = src[3];
		m[4] = src[4];   m[5] = src[5];  m[6] = src[6];   m[7] = src[7];
		m[8] = src[8];   m[9] = src[9];  m[10] = src[10]; m[11] = src[11];
		m[12] = src[12]; m[13] = src[13]; m[14] = src[14]; m[15] = src[15];
	}

	 CD::CDMatrix4::CDMatrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15)
	{
		m[0] = m0; m[1] = m1; m[2] = m2; m[3] = m3;
		m[4] = m4; m[5] = m5; m[6] = m6; m[7] = m7;
		m[8] = m8; m[9] = m9; m[10] = m10; m[11] = m11;
		m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
	}

	 CD::CDMatrix4::CDMatrix4(CDVector3 m012, float m3, CDVector3 m456, float m7, CDVector3 m8910, float m11, CDVector3 m121314, float m15)
	{
		m[0] = m012.x; m[1] = m012.y; m[2] = m012.z; m[3] = m3;
		m[4] = m456.x; m[5] = m456.y; m[6] = m456.z; m[7] = m7;
		m[8] = m8910.x; m[9] = m8910.y; m[10] = m8910.z; m[11] = m11;
		m[12] = m121314.x; m[13] = m121314.y; m[14] = m121314.z; m[15] = m15;
	}

	 CD::CDMatrix4::CDMatrix4(CDVector4 m0123, CDVector4 m4567, CDVector4 m891011, CDVector4 m12131415)
	{
		m[0] = m0123.x; m[1] = m0123.y; m[2] = m0123.z; m[3] = m0123.w;
		m[4] = m4567.x; m[5] = m4567.y; m[6] = m4567.z; m[7] = m4567.w;
		m[8] = m891011.x; m[9] = m891011.y; m[10] = m891011.z; m[11] = m891011.w;
		m[12] = m12131415.x; m[13] = m12131415.y; m[14] = m12131415.z; m[15] = m12131415.w;
	}


	CDMatrix4 CDMatrix4::get() const
	{
		return *this;
	}

	CDMatrix4 CDMatrix4::getTranspose()
	{
		CDMatrix4 tm;
		tm.m[0] = m[0];   tm.m[1] = m[4];   tm.m[2] = m[8];   tm.m[3] = m[12];
		tm.m[4] = m[1];   tm.m[5] = m[5];   tm.m[6] = m[9];   tm.m[7] = m[13];
		tm.m[8] = m[2];   tm.m[9] = m[6];   tm.m[10] = m[10];  tm.m[11] = m[14];
		tm.m[12] = m[3];   tm.m[13] = m[7];   tm.m[14] = m[11];  tm.m[15] = m[15];
		return tm;
	}



	 float CD::CDMatrix4::getDeterminant()
	{
		float deter;
		CDMatrix3 deter0 =
		{ m[5],m[6],m[7],
		m[9],m[10],m[11],
		m[13],m[14],m[15]
		};
		CDMatrix3 deter1 = {
		m[4],m[6],m[7],
		m[8],m[10],m[11],
		m[12],m[14],m[15]
		};
		CDMatrix3 deter2 = {
		m[4],m[5],m[7],
		m[8],m[9],m[11],
		m[12],m[13],m[15]
		};
		CDMatrix3 deter3 = {
		m[4],m[5],m[6],
		m[8],m[9],m[10],
		m[12],m[13],m[14]
		};
		deter = (m[0] * deter0.getDeterminant()) - (m[1] * deter1.getDeterminant()) + (m[2] * deter2.getDeterminant()) - (m[3] * deter3.getDeterminant());
		return deter;
	}

	 CD::CDMatrix4 & CD::CDMatrix4::identity()
	{
		m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
		m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
		m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
		m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
		return *this;
	}

	 CD::CDMatrix4 & CD::CDMatrix4::transpose()
	{
		std::swap(m[1], m[4]);
		std::swap(m[2], m[8]);
		std::swap(m[3], m[12]);
		std::swap(m[6], m[9]);
		std::swap(m[7], m[13]);
		std::swap(m[11], m[14]);

		return *this;
	}

	 CD::CDMatrix4 & CD::CDMatrix4::invert()
	{

		float determinant, invDeterminant;
		CDMatrix3 mat0 = {
		m[5],m[6] ,m[7],
		m[9] ,m[10] ,m[11],
		m[13] ,m[14] ,m[15] };
		CDMatrix3 mat1 = {
		m[4],m[6] ,m[7],
		m[8] ,m[10] ,m[11],
		m[12] ,m[14] ,m[15] };
		CDMatrix3 mat2 = {
		m[4],m[5] ,m[7],
		m[8] ,m[9] ,m[11],
		m[12] ,m[13] ,m[15] };
		CDMatrix3 mat3 = {
		m[4],m[5] ,m[6],
		m[8] ,m[9] ,m[10],
		m[12] ,m[13] ,m[14] };
		CDMatrix3 mat4 = {
		m[1],m[2] ,m[3],
		m[9] ,m[10] ,m[11],
		m[13] ,m[14] ,m[15] };
		CDMatrix3 mat5 = {
		m[0],m[2] ,m[3],
		m[8] ,m[10] ,m[11],
		m[12] ,m[14] ,m[15] };
		CDMatrix3 mat6 = {
		m[0],m[1] ,m[3],
		m[8] ,m[9] ,m[11],
		m[12] ,m[13] ,m[15] };
		CDMatrix3 mat7 = {
		m[0],m[1] ,m[2],
		m[8] ,m[9] ,m[10],
		m[12] ,m[13] ,m[14] };
		CDMatrix3 mat8 = {
		m[1],m[2] ,m[3],
		m[5] ,m[6] ,m[7],
		m[13] ,m[14] ,m[15] };
		CDMatrix3 mat9 = {
		m[0],m[2] ,m[3],
		m[4] ,m[6] ,m[7],
		m[12] ,m[14] ,m[15] };
		CDMatrix3 mat10 = {
		m[0],m[1] ,m[3],
		m[4] ,m[5] ,m[7],
		m[12] ,m[13] ,m[15] };
		CDMatrix3 mat11 = {
		m[0],m[1] ,m[2],
		m[4] ,m[5] ,m[6],
		m[12] ,m[13] ,m[14] };
		CDMatrix3 mat12 = {
		m[1],m[2] ,m[3],
		m[5] ,m[6] ,m[7],
		m[9] ,m[10] ,m[11] };
		CDMatrix3 mat13 = {
		m[0],m[2] ,m[3],
		m[4] ,m[6] ,m[7],
		m[8] ,m[10] ,m[11] };
		CDMatrix3 mat14 = {
		m[0],m[1] ,m[3],
		m[4] ,m[5] ,m[7],
		m[8] ,m[9] ,m[11] };
		CDMatrix3 mat15 = {
		m[0],m[1] ,m[2],
		m[4] ,m[5] ,m[6],
		m[8] ,m[9] ,m[10] };
		determinant = getDeterminant();
		if (determinant >= -0.00001f&&determinant <= 0.00001f)
		{
			return identity(); // cannot inverse, make it idenety matrix
		}
		invDeterminant = 1.0f / determinant;
		m[0] = (mat0.getDeterminant()*invDeterminant);
		m[1] = -(mat1.getDeterminant()*invDeterminant);
		m[2] = (mat2.getDeterminant()*invDeterminant);
		m[3] = -(mat3.getDeterminant()*invDeterminant);
		m[4] = -(mat4.getDeterminant()*invDeterminant);
		m[5] = (mat5.getDeterminant()*invDeterminant);
		m[6] = -(mat6.getDeterminant()*invDeterminant);
		m[7] = (mat7.getDeterminant()*invDeterminant);
		m[8] = (mat8.getDeterminant()*invDeterminant);
		m[9] = -(mat9.getDeterminant()*invDeterminant);
		m[10] = (mat10.getDeterminant()*invDeterminant);
		m[11] = -(mat11.getDeterminant()*invDeterminant);
		m[12] = -(mat12.getDeterminant()*invDeterminant);
		m[13] = (mat13.getDeterminant()*invDeterminant);
		m[14] = -(mat14.getDeterminant()*invDeterminant);
		m[15] = (mat15.getDeterminant()*invDeterminant);
		return *this;
	}

	 CDMatrix4 & CDMatrix4::translate(float x, float y, float z)
	{
		CDMatrix4 tras =
		{
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		};
		*this *= tras;
		return *this;
	}

	CDMatrix4 & CDMatrix4::translate(const CDVector3 & vec)
	{
		translate(vec.x, vec.y, vec.z);
		return *this;
	}

	CDMatrix4 & CDMatrix4::rotate(float angle, const CDVector3 & axis)
	{
		float c = cosf(angle);    // cosine
		float s = sinf(angle);    // sine
		CDVector3 vec = axis;
		vec.normalize();
		CDMatrix4 result =
		{
			c + ((vec.x*vec.x)*(1 - c))			,((vec.x*vec.y)*(1 - c)) - (vec.z*s)	,((vec.x*vec.z)*(1 - c)) + (vec.y*s),0,
			((vec.x*vec.y)*(1 - c)) + (vec.z*s)	,c + ((vec.y*vec.y)*(1 - c))		,((vec.y*vec.z)*(1 - c)) - (vec.x*s)	,0,
			((vec.x*vec.z)*(1 - c)) - (vec.y*s)	,((vec.y*vec.z)*(1 - c)) + (vec.x*s)	,c + ((vec.z*vec.z)*(1 - c)),0,
			0,0,0,1
		};
		*this *= result;
		return *this;
	}

	 CDMatrix4 & CDMatrix4::rotate(float angle, float x, float y, float z)
	{
		rotate(angle, CDVector3(x, y, z));
		return *this;
	}

	 CDMatrix4 & CDMatrix4::rotateX(float angle)
	{
		CDMatrix4 rotX =
		{
			1, 0, 0, 0,
			0, cosf(angle),-sinf(angle), 0,
			0, sinf(angle), cosf(angle), 0,
			0, 0, 0, 1
		};

		*this = *this * rotX;
		return *this;
	}

	 CDMatrix4 & CDMatrix4::rotateXstayPos(float angle)
	{
		CDMatrix4 rotX =
		{
			1, 0, 0, 0,
			0, cosf(angle),-sinf(angle), 0,
			0, sinf(angle), cosf(angle), 0,
			0, 0, 0, 1
		};
		*this = rotX * (*this);
		return *this;
	}

	CDMatrix4 & CDMatrix4::rotateY(float angle)
	{

		CDMatrix4 rotY = {
			cosf(angle), 0, sinf(angle), 0,
			0, 1, 0, 0,
			-sinf(angle), 0, cosf(angle), 0,
			0, 0, 0, 1
		};
		*this *= rotY;
		return *this;
	}

	 CDMatrix4 & CDMatrix4::rotateYstayPos(float angle)
	{
		CDMatrix4 rotY =
		{
			cos(angle), 0, sin(angle), 0,
			0, 1, 0, 0,
			-sin(angle), 0, cos(angle), 0,
			0, 0, 0, 1
		};
		*this = rotY * (*this);
		return *this;
	}

	 CDMatrix4 & CDMatrix4::rotateZ(float angle)
	{
		CDMatrix4 rotZ = {
			cosf(angle),-sinf(angle), 0, 0,
			sinf(angle), cosf(angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		*this *= rotZ;
		return *this;
	}

	 CDMatrix4 & CDMatrix4::rotateZstayPos(float angle)
	{
		CDMatrix4 rotZ = {
			cosf(angle),-sinf(angle), 0, 0,
			sinf(angle), cosf(angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		*this = rotZ * (*this);
		return *this;
	}

	 CDMatrix4 & CDMatrix4::scale(float scal)
	{
		scale(scal, scal, scal);
		return *this;
	}

	 CDMatrix4 & CDMatrix4::scale(float sx, float sy, float sz)
	{
		CDMatrix4 scal =
		{
			sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1
		};
		*this *= scal;
		return *this;
	}

	 CDMatrix4 CDMatrix4::operator+(const CDMatrix4 & mat) const
	{
		return CDMatrix4(
			m[0] + mat.m[0], m[1] + mat.m[1], m[0] + mat.m[2], m[3] + mat.m[3],
			m[4] + mat.m[4], m[5] + mat.m[5], m[6] + mat.m[6], m[7] + mat.m[7],
			m[8] + mat.m[8], m[9] + mat.m[9], m[10] + mat.m[10], m[11] + mat.m[11],
			m[12] + mat.m[12], m[13] + mat.m[13], m[14] + mat.m[14], m[15] + mat.m[15]);
	}

	 CDMatrix4 CDMatrix4::operator-(const CDMatrix4 & mat) const
	{
		return CDMatrix4(
			m[0] - mat.m[0], m[1] - mat.m[1], m[0] - mat.m[2], m[3] - mat.m[3],
			m[4] - mat.m[4], m[5] - mat.m[5], m[6] - mat.m[6], m[7] - mat.m[7],
			m[8] - mat.m[8], m[9] - mat.m[9], m[10] - mat.m[10], m[11] - mat.m[11],
			m[12] - mat.m[12], m[13] - mat.m[13], m[14] - mat.m[14], m[15] - mat.m[15]);
	}

	 CDMatrix4 & CDMatrix4::operator+=(const CDMatrix4 & mat)
	{
		m[0] += mat.m[0]; m[1] += mat.m[1]; m[0] += mat.m[2]; m[3] += mat.m[3];
		m[4] += mat.m[4]; m[5] += mat.m[5]; m[6] += mat.m[6]; m[7] += mat.m[7];
		m[8] += mat.m[8]; m[9] += mat.m[9]; m[10] += mat.m[10]; m[11] += mat.m[11];
		m[12] += mat.m[12]; m[13] += mat.m[13]; m[14] += mat.m[14]; m[15] += mat.m[15];
		return *this;
	}

	 CDMatrix4 & CDMatrix4::operator-=(const CDMatrix4 & mat)
	{
		m[0] -= mat.m[0]; m[1] -= mat.m[1]; m[0] -= mat.m[2]; m[3] -= mat.m[3];
		m[4] -= mat.m[4]; m[5] -= mat.m[5]; m[6] -= mat.m[6]; m[7] -= mat.m[7];
		m[8] -= mat.m[8]; m[9] -= mat.m[9]; m[10] -= mat.m[10]; m[11] -= mat.m[11];
		m[12] -= mat.m[12]; m[13] -= mat.m[13]; m[14] -= mat.m[14]; m[15] -= mat.m[15];
		return *this;
	}

	 CDVector4 CDMatrix4::operator*(const CDVector4 & vec) const
	{
		return CDVector4(
			m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3] * vec.z,
			m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7] * vec.z,
			m[8] * vec.x + m[9] * vec.y + m[10] * vec.z + m[11] * vec.z,
			m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15] * vec.z);
	}

	 CDVector3 CDMatrix4::operator*(const CDVector3 & vec) const
	{
		return CDVector3(
			m[0] * vec.x + m[1] * vec.y + m[2] * vec.z,
			m[4] * vec.x + m[5] * vec.y + m[6] * vec.z,
			m[8] * vec.x + m[9] * vec.y + m[10] * vec.z);
	}

	 CDMatrix4 CDMatrix4::operator*(const CDMatrix4 & mat) const
	{
		return CDMatrix4(
			((m[0] * mat.m[0]) + (m[1] * mat.m[4]) + (m[2] * mat.m[8]) + (m[3] * mat.m[12])), ((m[0] * mat.m[1]) + (m[1] * mat.m[5]) + (m[2] * mat.m[9]) + (m[3] * mat.m[13])), ((m[0] * mat.m[2]) + (m[1] * mat.m[6]) + (m[2] * mat.m[10]) + (m[3] * mat.m[14])), ((m[0] * mat.m[3]) + (m[1] * mat.m[7]) + (m[2] * mat.m[11]) + (m[3] * mat.m[15])),
			((m[4] * mat.m[0]) + (m[5] * mat.m[4]) + (m[6] * mat.m[8]) + (m[7] * mat.m[12])), ((m[4] * mat.m[1]) + (m[5] * mat.m[5]) + (m[6] * mat.m[9]) + (m[7] * mat.m[13])), ((m[4] * mat.m[2]) + (m[5] * mat.m[6]) + (m[6] * mat.m[10]) + (m[7] * mat.m[14])), ((m[4] * mat.m[3]) + (m[5] * mat.m[7]) + (m[6] * mat.m[11]) + (m[7] * mat.m[15])),
			((m[8] * mat.m[0]) + (m[9] * mat.m[4]) + (m[10] * mat.m[8]) + (m[11] * mat.m[12])), ((m[8] * mat.m[1]) + (m[9] * mat.m[5]) + (m[10] * mat.m[9]) + (m[11] * mat.m[13])), ((m[8] * mat.m[2]) + (m[9] * mat.m[6]) + (m[10] * mat.m[10]) + (m[11] * mat.m[14])), ((m[8] * mat.m[3]) + (m[9] * mat.m[7]) + (m[10] * mat.m[11]) + (m[11] * mat.m[15])),
			((m[12] * mat.m[0]) + (m[13] * mat.m[4]) + (m[14] * mat.m[8]) + (m[15] * mat.m[12])), ((m[12] * mat.m[1]) + (m[13] * mat.m[5]) + (m[14] * mat.m[9]) + (m[15] * mat.m[13])), ((m[12] * mat.m[2]) + (m[13] * mat.m[6]) + (m[14] * mat.m[10]) + (m[15] * mat.m[14])), ((m[12] * mat.m[3]) + (m[13] * mat.m[7]) + (m[14] * mat.m[11]) + (m[15] * mat.m[15])));

	}

	 CDMatrix4 & CDMatrix4::operator*=(const CDMatrix4 & mat)
	{
		*this = *this*mat;
		return *this;
	}

	 bool CDMatrix4::operator==(const CDMatrix4 & mat) const
	{
		return (m[0] == mat.m[0]) && (m[1] == mat.m[1]) && (m[2] == mat.m[2]) && (m[3] == mat.m[3]) &&
			(m[4] == mat.m[4]) && (m[5] == mat.m[5]) && (m[6] == mat.m[6]) && (m[7] == mat.m[7]) &&
			(m[8] == mat.m[8]) && (m[9] == mat.m[9]) && (m[10] == mat.m[10]) && (m[11] == mat.m[11]) &&
			(m[12] == mat.m[12]) && (m[13] == mat.m[13]) && (m[14] == mat.m[14]) && (m[15] == mat.m[15]);
	}

	 bool CDMatrix4::operator!=(const CDMatrix4 & mat) const
	{
		return (m[0] != mat.m[0]) || (m[1] != mat.m[1]) || (m[2] != mat.m[2]) || (m[3] != mat.m[3]) ||
			(m[4] != mat.m[4]) || (m[5] != mat.m[5]) || (m[6] != mat.m[6]) || (m[7] != mat.m[7]) ||
			(m[8] != mat.m[8]) || (m[9] != mat.m[9]) || (m[10] != mat.m[10]) || (m[11] != mat.m[11]) ||
			(m[12] != mat.m[12]) || (m[13] != mat.m[13]) || (m[14] != mat.m[14]) || (m[15] != mat.m[15]);
	}

	 float CDMatrix4::operator[](int index) const
	{
		return m[index];
	}

	 float & CDMatrix4::operator[](int index)
	{
		return m[index];
	}

	CDMatrix4 operator-(const CDMatrix4 & mat)
	{
		return CDMatrix4(-mat[0], -mat[1], -mat[2], -mat[3],
			-mat[4], -mat[5], -mat[6], -mat[7],
			-mat[8], -mat[9], -mat[10], -mat[11],
			-mat[12], -mat[13], -mat[14], -mat[15]);
	}

	CDMatrix4 operator*(float scalar, const CDMatrix4 & mat)
	{
		return CDMatrix4(scalar*mat[0], scalar*mat[1], scalar*mat[2], scalar*mat[3],
			scalar*mat[4], scalar*mat[5], scalar*mat[6], scalar*mat[7],
			scalar*mat[8], scalar*mat[9], scalar*mat[10], scalar*mat[11],
			scalar*mat[12], scalar*mat[13], scalar*mat[14], scalar*mat[15]);
	}

	CDVector3 operator*(const CDVector3 & vec, const CDMatrix4 & mat)
	{
		return CDVector3(
			mat[0] * vec.x + mat[4] * vec.y + mat[8] * vec.z,
			mat[1] * vec.x + mat[5] * vec.y + mat[9] * vec.z,
			mat[2] * vec.x + mat[6] * vec.y + mat[10] * vec.z);
	}

	CDVector4 operator*(const CDVector4 & vec, const CDMatrix4 & mat)
	{
		return CDVector4(
			mat[0] * vec.x + mat[4] * vec.y + mat[8] * vec.z + mat[12] * vec.z,
			mat[1] * vec.x + mat[5] * vec.y + mat[9] * vec.z + mat[13] * vec.z,
			mat[2] * vec.x + mat[6] * vec.y + mat[10] * vec.z + mat[14] * vec.z,
			mat[3] * vec.x + mat[7] * vec.y + mat[11] * vec.z + mat[15] * vec.z);
	}

	 std::ostream & CD::operator<<(std::ostream & os, const CDMatrix4 & m)
	{
		os << std::fixed << std::setprecision(5);
		os << "[" << std::setw(10) << m.m[0] << " " << std::setw(10) << m.m[1] << " " << std::setw(10) << m.m[2] << " " << std::setw(10) << m.m[3] << "]\n"
			<< "[" << std::setw(10) << m.m[4] << " " << std::setw(10) << m.m[5] << " " << std::setw(10) << m.m[6] << " " << std::setw(10) << m.m[7] << "]\n"
			<< "[" << std::setw(10) << m.m[8] << " " << std::setw(10) << m.m[9] << " " << std::setw(10) << m.m[10] << " " << std::setw(10) << m.m[11] << "]\n"
			<< "[" << std::setw(10) << m.m[12] << " " << std::setw(10) << m.m[13] << " " << std::setw(10) << m.m[14] << " " << std::setw(10) << m.m[15] << "]\n";
		os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
		return os;
	}
	CDMatrix4 transposeMatrix(const CDMatrix4 & mat)
	{
		return CDMatrix4(
			mat[0], mat[4], mat[8], mat[12],
			mat[1], mat[5], mat[9], mat[13],
			mat[2], mat[6], mat[10], mat[14],
			mat[3], mat[7], mat[11], mat[15]
		);
	}
	CDMatrix4 invertMatrix(const CDMatrix4 & mat)
	{
		float determinant, invDeterminant;
		CDMatrix3 mat0 = {
		mat[5],mat[6] ,mat[7],
		mat[9] ,mat[10] ,mat[11],
		mat[13] ,mat[14] ,mat[15] };
		CDMatrix3 mat1 = {
		mat[4],mat[6] ,mat[7],
		mat[8] ,mat[10] ,mat[11],
		mat[12] ,mat[14] ,mat[15] };
		CDMatrix3 mat2 = {
		mat[4],mat[5] ,mat[7],
		mat[8] ,mat[9] ,mat[11],
		mat[12] ,mat[13] ,mat[15] };
		CDMatrix3 mat3 = {
		mat[4],mat[5] ,mat[6],
		mat[8] ,mat[9] ,mat[10],
		mat[12] ,mat[13] ,mat[14] };
		CDMatrix3 mat4 = {
		mat[1],mat[2] ,mat[3],
		mat[9] ,mat[10] ,mat[11],
		mat[13] ,mat[14] ,mat[15] };
		CDMatrix3 mat5 = {
		mat[0],mat[2] ,mat[3],
		mat[8] ,mat[10] ,mat[11],
		mat[12] ,mat[14] ,mat[15] };
		CDMatrix3 mat6 = {
		mat[0],mat[1] ,mat[3],
		mat[8] ,mat[9] ,mat[11],
		mat[12] ,mat[13] ,mat[15] };
		CDMatrix3 mat7 = {
		mat[0],mat[1] ,mat[2],
		mat[8] ,mat[9] ,mat[10],
		mat[12] ,mat[13] ,mat[14] };
		CDMatrix3 mat8 = {
		mat[1],mat[2] ,mat[3],
		mat[5] ,mat[6] ,mat[7],
		mat[13] ,mat[14] ,mat[15] };
		CDMatrix3 mat9 = {
		mat[0],mat[2] ,mat[3],
		mat[4] ,mat[6] ,mat[7],
		mat[12] ,mat[14] ,mat[15] };
		CDMatrix3 mat10 = {
		mat[0],mat[1] ,mat[3],
		mat[4] ,mat[5] ,mat[7],
		mat[12] ,mat[13] ,mat[15] };
		CDMatrix3 mat11 = {
		mat[0],mat[1] ,mat[2],
		mat[4] ,mat[5] ,mat[6],
		mat[12] ,mat[13] ,mat[14] };
		CDMatrix3 mat12 = {
		mat[1],mat[2] ,mat[3],
		mat[5] ,mat[6] ,mat[7],
		mat[9] ,mat[10] ,mat[11] };
		CDMatrix3 mat13 = {
		mat[0],mat[2] ,mat[3],
		mat[4] ,mat[6] ,mat[7],
		mat[8] ,mat[10] ,mat[11] };
		CDMatrix3 mat14 = {
		mat[0],mat[1] ,mat[3],
		mat[4] ,mat[5] ,mat[7],
		mat[8] ,mat[9] ,mat[11] };
		CDMatrix3 mat15 = {
		mat[0],mat[1] ,mat[2],
		mat[4] ,mat[5] ,mat[6],
		mat[8] ,mat[9] ,mat[10] };
		CDMatrix4 result = mat;
		determinant = result.getDeterminant();
		if (determinant >= -0.00001f&&determinant <= 0.00001f)
		{
			return result.identity(); // cannot inverse, make it idenety matrix
		}
		invDeterminant = 1.0f / determinant;
		result.m[0] = (mat0.getDeterminant()*invDeterminant);
		result.m[1] = -(mat1.getDeterminant()*invDeterminant);
		result.m[2] = (mat2.getDeterminant()*invDeterminant);
		result.m[3] = -(mat3.getDeterminant()*invDeterminant);
		result.m[4] = -(mat4.getDeterminant()*invDeterminant);
		result.m[5] = (mat5.getDeterminant()*invDeterminant);
		result.m[6] = -(mat6.getDeterminant()*invDeterminant);
		result.m[7] = (mat7.getDeterminant()*invDeterminant);
		result.m[8] = (mat8.getDeterminant()*invDeterminant);
		result.m[9] = -(mat9.getDeterminant()*invDeterminant);
		result.m[10] = (mat10.getDeterminant()*invDeterminant);
		result.m[11] = -(mat11.getDeterminant()*invDeterminant);
		result.m[12] = -(mat12.getDeterminant()*invDeterminant);
		result.m[13] = (mat13.getDeterminant()*invDeterminant);
		result.m[14] = -(mat14.getDeterminant()*invDeterminant);
		result.m[15] = (mat15.getDeterminant()*invDeterminant);
		return result;
	}
	CDMatrix4 identityMatrix()
	{
		CDMatrix4 ident =
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
		return ident;
	}
	CDMatrix4 matrix4Translate(float x, float y, float z)
	{
		CDMatrix4 tras = matrix4Translate(CDVector3(x, y, z));
		return CDMatrix4();
	}
	CDMatrix4 matrix4Translate(const CDVector3 & vec)
	{
		CDMatrix4 tras =
		{
			1, 0, 0, vec.x,
			0, 1, 0, vec.y,
			0, 0, 1, vec.z,
			0, 0, 0, 1
		};
		return tras;
	}
	CDMatrix4 matrix4Rotate(float angle, const CDVector3 & axis)
	{
		float c = cosf(angle);    // cosine
		float s = sinf(angle);    // sine
		CDVector3 vec = axis;
		vec.normalize();
		CDMatrix4 result =
		{
			c + ((vec.x*vec.x)*(1 - c))			,((vec.x*vec.y)*(1 - c)) - (vec.z*s)	,((vec.x*vec.z)*(1 - c)) + (vec.y*s),0,
			((vec.x*vec.y)*(1 - c)) + (vec.z*s)	,c + ((vec.y*vec.y)*(1 - c))		,((vec.y*vec.z)*(1 - c)) - (vec.x*s)	,0,
			((vec.x*vec.z)*(1 - c)) - (vec.y*s)	,((vec.y*vec.z)*(1 - c)) + (vec.x*s)	,c + ((vec.z*vec.z)*(1 - c)),0,
			0,0,0,1
		};
		return result;
	}
	CDMatrix4 matrix4Rotate(float angle, float x, float y, float z)
	{
		CDMatrix4 result = matrix4Rotate(angle, CDVector3(x, y, z));
		return result;
	}
	CDMatrix4 matrix4RotateX(float angle)
	{
		CDMatrix4 rotX =
		{
			1, 0, 0, 0,
			0, cosf(angle),sinf(angle), 0,
			0, -sinf(angle), cosf(angle), 0,
			0, 0, 0, 1
		};
		return rotX;
	}
	CDMatrix4 matrix4RotateY(float angle)
	{
		CDMatrix4 rotY = {
			cosf(angle), 0, -sinf(angle), 0,
			0, 1, 0, 0,
			sinf(angle), 0, cosf(angle), 0,
			0, 0, 0, 1
		};
		return rotY;
	}
	CDMatrix4 matrix4RotateZ(float angle)
	{
		CDMatrix4 rotZ = {
			cosf(angle), sinf(angle), 0, 0,
			-sinf(angle), cosf(angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		return rotZ;
	}
	CDMatrix4 matrix4Scale(float scale)
	{
		CDMatrix4 sca = matrix4Scale(scale, scale, scale);
		return sca;
	}
	CDMatrix4 matrix4Scale(float sx, float sy, float sz)
	{
		CDMatrix4 sca = {
			sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1
		};
		return sca;
	}
}