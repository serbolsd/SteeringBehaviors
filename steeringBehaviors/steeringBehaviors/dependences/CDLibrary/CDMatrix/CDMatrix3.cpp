#include <CDMatrix/CDMatrix3.h>


inline CD::CDMatrix3::CDMatrix3()
{
	m[0] = 1; m[1] = 0; m[2] = 0;
	m[3] = 0; m[4] = 1; m[5] = 0;
	m[6] = 0; m[7] = 0; m[8] = 1;
}

inline CD::CDMatrix3::CDMatrix3(const float src[9])
{
	m[0] = src[0]; m[1] = src[1]; m[2] = src[2];
	m[3] = src[3]; m[4] = src[4]; m[5] = src[5];
	m[6] = src[6]; m[7] = src[7]; m[8] = src[8];
}

inline CD::CDMatrix3::CDMatrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8)
{
	m[0] = m0; m[1] = m1; m[2] = m2;
	m[3] = m3; m[4] = m4; m[5] = m5;
	m[6] = m6; m[7] = m7; m[8] = m8;
}

inline CD::CDMatrix3::CDMatrix3(const CDVector3 & m012, const CDVector3 & m345, const CDVector3 & m678)
{
	m[0] = m012.x; m[1] = m012.y; m[2] = m012.z;
	m[3] = m012.x; m[4] = m012.y; m[5] = m012.z;
	m[6] = m678.x; m[7] = m678.y; m[8] = m678.z;
}

inline const float * CD::CDMatrix3::get() const
{
	return m;
}

inline float CD::CDMatrix3::getDeterminant()
{
	return (m[0] * m[4] * m[8]) + (m[1] * m[5] * m[6]) + (m[2] * m[3] * m[7]) - (m[0] * m[5] * m[7]) -
		(m[1] * m[3] * m[8]) - (m[2] * m[4] * m[6]);
}

inline CD::CDMatrix3 & CD::CDMatrix3::identity()
{
	m[0] = 1; m[1] = 0; m[2] = 0;
	m[3] = 0; m[4] = 1; m[5] = 0;
	m[6] = 0; m[7] = 0; m[8] = 1;
	return *this;
}

inline CD::CDMatrix3 & CD::CDMatrix3::transpose()
{
	std::swap(m[1], m[3]);
	std::swap(m[2], m[6]);
	std::swap(m[5], m[7]);

	return *this;
}

inline CD::CDMatrix3 CD::CDMatrix3::getTranspose()
{
	CDMatrix3 trans = *this;
	std::swap(trans.m[1], trans.m[3]);
	std::swap(trans.m[2], trans.m[6]);
	std::swap(trans.m[5], trans.m[7]);
	return trans;
}

inline CD::CDMatrix3 & CD::CDMatrix3::invert()
{
	float determinant, invDeterminant;
	float tmp[9];

	tmp[0] = (m[4] * m[8] - m[5] * m[7]);
	tmp[1] = -(m[3] * m[8] - m[5] * m[6]);
	tmp[2] = (m[3] * m[7] - m[4] * m[6]);
	tmp[3] = -(m[1] * m[8] - m[2] * m[7]);
	tmp[4] = (m[0] * m[8] - m[2] * m[6]);
	tmp[5] = -(m[0] * m[7] - m[1] * m[6]);
	tmp[6] = (m[1] * m[5] - m[2] * m[4]);
	tmp[7] = -(m[0] * m[5] - m[2] * m[3]);
	tmp[8] = (m[0] * m[4] - m[1] * m[3]);

	// check determinant if it is 0
	determinant = getDeterminant();
	if (determinant >= -0.00001f&&determinant <= 0.00001f)
	{
		return identity(); // cannot inverse, make it idenety matrix
	}

	// divide by the determinant
	invDeterminant = 1.0f / determinant;
	m[0] = invDeterminant * tmp[0];
	m[1] = invDeterminant * tmp[1];
	m[2] = invDeterminant * tmp[2];
	m[3] = invDeterminant * tmp[3];
	m[4] = invDeterminant * tmp[4];
	m[5] = invDeterminant * tmp[5];
	m[6] = invDeterminant * tmp[6];
	m[7] = invDeterminant * tmp[7];
	m[8] = invDeterminant * tmp[8];
	transpose();

	return *this;
}

inline CD::CDMatrix3 CD::CDMatrix3::getInvert()
{
	CDMatrix3 inver = *this;
	float determinant, invDeterminant;
	float tmp[9];

	tmp[0] = (inver.m[4] * inver.m[8] - inver.m[5] * inver.m[7]);
	tmp[1] = -(inver.m[3] * inver.m[8] - inver.m[5] * inver.m[6]);
	tmp[2] = (inver.m[3] * inver.m[7] - inver.m[4] * inver.m[6]);
	tmp[3] = -(inver.m[1] * inver.m[8] - inver.m[2] * inver.m[7]);
	tmp[4] = (inver.m[0] * inver.m[8] - inver.m[2] * inver.m[6]);
	tmp[5] = -(inver.m[0] * inver.m[7] - inver.m[1] * inver.m[6]);
	tmp[6] = (inver.m[1] * inver.m[5] - inver.m[2] * inver.m[4]);
	tmp[7] = -(inver.m[0] * inver.m[5] - inver.m[2] * inver.m[3]);
	tmp[8] = (inver.m[0] * inver.m[4] - inver.m[1] * inver.m[3]);

	// check determinant if it is 0
	determinant = getDeterminant();
	if (determinant >= -0.00001f&&determinant <= 0.00001f)
	{
		return inver.identity(); // cannot inverse, make it idenety matrix
	}

	// divide by the determinant
	invDeterminant = 1.0f / determinant;
	inver.m[0] = invDeterminant * tmp[0];
	inver.m[1] = invDeterminant * tmp[1];
	inver.m[2] = invDeterminant * tmp[2];
	inver.m[3] = invDeterminant * tmp[3];
	inver.m[4] = invDeterminant * tmp[4];
	inver.m[5] = invDeterminant * tmp[5];
	inver.m[6] = invDeterminant * tmp[6];
	inver.m[7] = invDeterminant * tmp[7];
	inver.m[8] = invDeterminant * tmp[8];
	inver.transpose();

	return inver;
}

inline CD::CDMatrix3 & CD::CDMatrix3::translate(float x, float y)
{
	translate(CDVector2(x, y));
	return *this;
}

inline CD::CDMatrix3 & CD::CDMatrix3::translate(const CDVector2 & vec)
{
	CDMatrix3 tras =
	{
		1,0,vec.x,
		0,1,vec.y,
		0,0,1
	};
	*this *= tras;
	return *this;
}

inline CD::CDMatrix3 & CD::CDMatrix3::rotate(float angle)
{
	CDMatrix3 rot =
	{
		cos(angle), -sin(angle),0,
		sin(angle), cos(angle),0,
		0,0,1
	};
	*this *= rot;
	return *this;
}

inline CD::CDMatrix3 & CD::CDMatrix3::scale(float scal)
{
	scale(scal, scal);
	return *this;
}

inline CD::CDMatrix3 & CD::CDMatrix3::scale(float sx, float sy)
{
	CDMatrix3 sca =
	{
		sx,0,0,
		0,sy,0,
		0,0,1
	};
	*this *= sca;
	return *this;
}

inline CD::CDMatrix3 & CD::CDMatrix3::shearX(float lenght)
{
	CDMatrix3 shear =
	{
		1,tan(lenght),0,
		0,1,0,
		0,0,1
	};
	*this *= shear;
	return *this;
}

inline CD::CDMatrix3 & CD::CDMatrix3::shearY(float lenght)
{
	CDMatrix3 shear =
	{
		1,0,0,
		tan(lenght),1,0,
		0,0,1
	};
	*this *= shear;
	return *this;
}

inline CD::CDMatrix3 CD::CDMatrix3::operator+(const CDMatrix3 & mat) const
{
	return CDMatrix3(
		m[0] + mat.m[0], m[1] + mat.m[1], m[0] + mat.m[2],
		m[3] + mat.m[3], m[4] + mat.m[4], m[5] + mat.m[5],
		m[6] + mat.m[6], m[7] + mat.m[7], m[8] + mat.m[8]);
}

inline CD::CDMatrix3 CD::CDMatrix3::operator-(const CDMatrix3 & mat) const
{
	return CDMatrix3(
		m[0] - mat.m[0], m[1] - mat.m[1], m[0] - mat.m[2],
		m[3] - mat.m[3], m[4] - mat.m[4], m[5] - mat.m[5],
		m[6] - mat.m[6], m[7] - mat.m[7], m[8] - mat.m[8]);
}

inline CD::CDMatrix3 & CD::CDMatrix3::operator+=(const CDMatrix3 & mat)
{
	m[0] += mat.m[0]; m[1] += mat.m[1]; m[0] += mat.m[2];
	m[3] += mat.m[3]; m[4] += mat.m[4]; m[5] += mat.m[5];
	m[6] += mat.m[6]; m[7] += mat.m[7]; m[8] += mat.m[8];
	return *this;
}

inline CD::CDMatrix3 & CD::CDMatrix3::operator-=(const CDMatrix3 & mat)
{
	m[0] -= mat.m[0]; m[1] -= mat.m[1]; m[0] -= mat.m[2];
	m[3] -= mat.m[3]; m[4] -= mat.m[4]; m[5] -= mat.m[5];
	m[6] -= mat.m[6]; m[7] -= mat.m[7]; m[8] -= mat.m[8];
	return *this;
}

inline CD::CDVector3 CD::CDMatrix3::operator*(const CDVector3 & vec) const
{
	return CDVector3(
		m[0] * vec.x + m[3] * vec.y + m[6] * vec.z,
		m[1] * vec.x + m[4] * vec.y + m[7] * vec.z,
		m[2] * vec.x + m[5] * vec.y + m[8] * vec.z);
}

inline CD::CDMatrix3 CD::CDMatrix3::operator*(const CDMatrix3 & mat) const
{
	return CDMatrix3(
		((m[0] * mat.m[0]) + (m[1] * mat.m[3]) + (m[2] * mat.m[6])), ((m[0] * mat.m[1]) + (m[1] * mat.m[4]) + (m[2] * mat.m[7])), ((m[0] * mat.m[2]) + (m[1] * mat.m[5]) + (m[2] * mat.m[8])),
		((m[3] * mat.m[0]) + (m[4] * mat.m[3]) + (m[5] * mat.m[6])), ((m[3] * mat.m[1]) + (m[4] * mat.m[4]) + (m[5] * mat.m[7])), ((m[3] * mat.m[2]) + (m[4] * mat.m[5]) + (m[5] * mat.m[8])),
		((m[6] * mat.m[0]) + (m[7] * mat.m[3]) + (m[8] * mat.m[6])), ((m[6] * mat.m[1]) + (m[7] * mat.m[4]) + (m[8] * mat.m[7])), ((m[6] * mat.m[2]) + (m[7] * mat.m[5]) + (m[8] * mat.m[8])));
}

inline CD::CDMatrix3 & CD::CDMatrix3::operator*=(const CDMatrix3 & mat)
{
	*this = *this*mat;
	return *this;
}

inline bool CD::CDMatrix3::operator==(const CDMatrix3 & mat) const
{
	return (m[0] == mat.m[0]) && (m[1] == mat.m[1]) && (m[2] == mat.m[2])
		&& (m[3] == mat.m[3]) && (m[4] == mat.m[4]) && (m[5] == mat.m[5])
		&& (m[6] == mat.m[6]) && (m[7] == mat.m[7]) && (m[8] == mat.m[8]);
}

inline bool CD::CDMatrix3::operator!=(const CDMatrix3 & mat) const
{
	return (m[0] != mat.m[0]) || (m[1] != mat.m[1]) || (m[2] != mat.m[2])
		|| (m[3] != mat.m[3]) || (m[4] != mat.m[4]) || (m[5] != mat.m[5])
		|| (m[6] != mat.m[6]) || (m[7] != mat.m[7]) || (m[8] != mat.m[8]);
}

inline float CD::CDMatrix3::operator[](int index) const
{
	return m[index];
}

inline float & CD::CDMatrix3::operator[](int index)
{
	return m[index];
}

inline CD::CDMatrix3 CD::operator-(const CDMatrix3 & mat)
{
	return CDMatrix3(-mat.m[0], -mat.m[1], -mat.m[2], -mat.m[3], -mat.m[4], -mat.m[5], -mat.m[6], -mat.m[7], -mat.m[8]);
}

inline CD::CDMatrix3 CD::operator*(float scalar, const CDMatrix3 & mat)
{
	return CDMatrix3(scalar*mat.m[0], scalar*mat.m[1], scalar*mat.m[2], scalar*mat.m[3], scalar*mat.m[4], scalar*mat.m[5], scalar*mat.m[6], scalar*mat.m[7], scalar*mat.m[8]);
}

inline CD::CDVector3 CD::operator*(const CDVector3 & vec, const CDMatrix3 & mat)
{
	return CDVector3(
		mat.m[0] * vec.x + mat.m[1] * vec.y + mat.m[2] * vec.z,
		mat.m[3] * vec.x + mat.m[4] * vec.y + mat.m[5] * vec.z,
		mat.m[6] * vec.x + mat.m[7] * vec.y + mat.m[8] * vec.z);
}

inline std::ostream & CD::operator<<(std::ostream & os, const CDMatrix3 & m)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << m.m[0] << " " << std::setw(10) << m.m[1] << " " << std::setw(10) << m.m[2] << "]\n"
		<< "[" << std::setw(10) << m.m[3] << " " << std::setw(10) << m.m[4] << " " << std::setw(10) << m.m[5] << "]\n"
		<< "[" << std::setw(10) << m.m[6] << " " << std::setw(10) << m.m[7] << " " << std::setw(10) << m.m[8] << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}

inline CD::CDMatrix3 CD::matrix3Transpose(const CDMatrix3 & mat)
{
	CDMatrix3 trans = mat;
	std::swap(trans.m[1], trans.m[3]);
	std::swap(trans.m[2], trans.m[6]);
	std::swap(trans.m[5], trans.m[7]);
	return trans;
}

inline CD::CDMatrix3 CD::matrix3Invert(const CDMatrix3 & mat)
{
	CDMatrix3 inver = mat;
	float determinant, invDeterminant;
	float tmp[9];

	tmp[0] = (inver.m[4] * inver.m[8] - inver.m[5] * inver.m[7]);
	tmp[1] = -(inver.m[3] * inver.m[8] - inver.m[5] * inver.m[6]);
	tmp[2] = (inver.m[3] * inver.m[7] - inver.m[4] * inver.m[6]);
	tmp[3] = -(inver.m[1] * inver.m[8] - inver.m[2] * inver.m[7]);
	tmp[4] = (inver.m[0] * inver.m[8] - inver.m[2] * inver.m[6]);
	tmp[5] = -(inver.m[0] * inver.m[7] - inver.m[1] * inver.m[6]);
	tmp[6] = (inver.m[1] * inver.m[5] - inver.m[2] * inver.m[4]);
	tmp[7] = -(inver.m[0] * inver.m[5] - inver.m[2] * inver.m[3]);
	tmp[8] = (inver.m[0] * inver.m[4] - inver.m[1] * inver.m[3]);

	// check determinant if it is 0
	determinant = inver.getDeterminant();
	if (determinant >= -0.00001f&&determinant <= 0.00001f)
	{
		return inver.identity(); // cannot inverse, make it idenety matrix
	}

	// divide by the determinant
	invDeterminant = 1.0f / determinant;
	inver.m[0] = invDeterminant * tmp[0];
	inver.m[1] = invDeterminant * tmp[1];
	inver.m[2] = invDeterminant * tmp[2];
	inver.m[3] = invDeterminant * tmp[3];
	inver.m[4] = invDeterminant * tmp[4];
	inver.m[5] = invDeterminant * tmp[5];
	inver.m[6] = invDeterminant * tmp[6];
	inver.m[7] = invDeterminant * tmp[7];
	inver.m[8] = invDeterminant * tmp[8];
	inver.transpose();

	return inver;
}

CD::CDMatrix3 CD::matrix3Identity()
{
	CD::CDMatrix3 ident =
	{
		1,0,0,
		0,1,0,
		0,0,1
	};
	return ident;
}

CD::CDMatrix3 CD::matrix3Translate(float x, float y)
{
	CD::CDMatrix3 tras = CD::matrix3Translate(CD::CDVector2(x, y));
	return tras;
}

CD::CDMatrix3 CD::matrix3Translate(const CD::CDVector2 & vec)
{
	CD::CDMatrix3 tras =
	{
		1,0,vec.x,
		0,1,vec.y,
		0,0,1
	};
	return tras;
}

CD::CDMatrix3 CD::matrix3Rotate(float angle)
{
	CD::CDMatrix3 rot =
	{
		cos(angle), -sin(angle),0,
		sin(angle), cos(angle),0,
		0,0,1
	};
	return rot;
}

CD::CDMatrix3 CD::matrix3Scale(float scale)
{
	CD::CDMatrix3 scal = matrix3Scale(scale, scale);
	return scal;
}

CD::CDMatrix3 CD::matrix3Scale(float sx, float sy)
{
	CD::CDMatrix3 scal =
	{
		sx,0,0,
		0,sy,0,
		0,0,1
	};
	return scal;
}