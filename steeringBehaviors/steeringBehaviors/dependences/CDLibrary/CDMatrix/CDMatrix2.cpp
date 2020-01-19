#include <CDMatrix/CDMatrix2.h>
inline CD::CDMatrix2::CDMatrix2()
{
	m[0] = 1; m[1] = 0;
	m[2] = 0; m[3] = 1;
}

inline CD::CDMatrix2::CDMatrix2(const float src[4])
{
	m[0] = src[0]; m[1] = src[1];
	m[2] = src[2]; m[3] = src[3];
}

inline CD::CDMatrix2::CDMatrix2(float m0, float m1, float m2, float m3)
{
	m[0] = m0; m[1] = m1;
	m[2] = m2; m[3] = m3;
}

inline CD::CDMatrix2::CDMatrix2(const CDVector2 & m0m1, float m2, float m3)
{
	m[0] = m0m1.x; m[1] = m0m1.y;
	m[2] = m2; m[3] = m3;
}

inline CD::CDMatrix2::CDMatrix2(float m0, float m1, const CDVector2 & m2m3)
{
	m[0] = m0; m[1] = m1;
	m[2] = m2m3.x; m[3] = m2m3.y;
}

inline CD::CDMatrix2::CDMatrix2(const CDVector2 & m0m1, const CDVector2 & m2m3)
{
	m[0] = m0m1.x; m[1] = m0m1.y;
	m[2] = m2m3.x; m[3] = m2m3.y;
}

//void CD::CDMatrix2::set(const float src[4])
//{
//	m[0] = src[0]; m[1] = src[1];
//	m[2] = src[2]; m[3] = src[3];
//}
//
//void CD::CDMatrix2::set(float m0, float m1, float m2, float m3)
//{
//	m[0] = m0; m[1] = m1;
//	m[2] = m2; m[3] = m3;
//}
//
//void CD::CDMatrix2::set(const CDVector2 & m0m1, float m2, float m3)
//{
//	m[0] = m0m1.x; m[1] = m0m1.y;
//	m[2] = m2; m[3] = m3;
//}
//
//void CD::CDMatrix2::set(float m0, float m1, const CDVector2 & m2m3)
//{
//	m[0] = m0; m[1] = m1;
//	m[2] = m2m3.x; m[3] = m2m3.y;
//}
//
//void CD::CDMatrix2::set(const CDVector2 & m0m1, const CDVector2 & m2m3)
//{
//	m[0] = m0m1.x; m[1] = m0m1.y;
//	m[2] = m2m3.x; m[3] = m2m3.y;
//}
//
//void CD::CDMatrix2::setRow(int index, const float & row0, const float & row1)//start in 0
//{
//	m[index * 2] = row0;  m[index * 2 + 1] = row1;
//}
//
//void CD::CDMatrix2::setRow(int index, const float row[2])
//{
//	m[index * 2] = row[0];  m[index * 2 + 1] = row[1];
//}
//
//void CD::CDMatrix2::setRow(int index, const CDVector2 & vec)
//{
//	m[index * 2] = vec[0];  m[index * 2 + 1] = vec[1];
//}
//
//void CD::CDMatrix2::setColumn(int index, const float & col0, const float & col1)
//{
//	m[index] = col0;  m[index + 2] = col1;
//}
//
//void CD::CDMatrix2::setColumn(int index, const float col[2])
//{
//	m[index] = col[0];  m[index + 2] = col[1];
//}
//
//void CD::CDMatrix2::setColumn(int index, const CDVector2 & vec)
//{
//	m[index] = vec[0];  m[index + 2] = vec[1];
//}

inline CD::CDMatrix2 CD::CDMatrix2::operator+(const CDMatrix2 & mat) const
{
	return CDMatrix2(m[0] + mat[0], m[1] + mat[1], m[2] + mat[2], m[3] + mat[3]);
}

inline CD::CDMatrix2 CD::CDMatrix2::operator-(const CDMatrix2 & mat) const
{
	return CDMatrix2(m[0] - mat[0], m[1] - mat[1], m[2] - mat[2], m[3] - mat[3]);
}

inline CD::CDMatrix2 & CD::CDMatrix2::operator+=(const CDMatrix2 & mat)
{
	m[0] += mat[0], m[1] += mat[1], m[2] += mat[2], m[3] += mat[3];
	return *this;
}

inline CD::CDMatrix2 & CD::CDMatrix2::operator-=(const CDMatrix2 & mat)
{
	m[0] -= mat[0], m[1] -= mat[1], m[2] -= mat[2], m[3] -= mat[3];
	return *this;
}

inline CD::CDVector2 CD::CDMatrix2::operator*(const CDVector2 & vec) const
{
	return CDVector2(m[0] * vec.x + m[1] * vec.y, m[2] * vec.x + m[3] * vec.y);
}

inline CD::CDMatrix2 CD::CDMatrix2::operator*(const CDMatrix2 & mat) const
{
	return CDMatrix2(
		m[0] * mat[0] + m[1] * mat[2], m[0] * mat[1] + m[1] * mat[3],
		m[2] * mat[0] + m[3] * mat[2], m[2] * mat[1] + m[3] * mat[3]);
}

inline CD::CDMatrix2 & CD::CDMatrix2::operator*=(const CDMatrix2 & mat)
{
	*this = *this * mat;
	return *this;
}

inline CD::CDMatrix2 & CD::CDMatrix2::operator=(const CDMatrix2 & mat)
{
	m[0] = mat[0], m[1] = mat[1], m[2] = mat[2], m[3] = mat[3];
	return *this;
}

inline bool CD::CDMatrix2::operator==(const CDMatrix2 & mat) const
{
	return (m[0] == mat.m[0]) && (m[1] == mat.m[1]) && (m[2] == mat.m[2]) && (m[3] == mat.m[3]);
}

inline bool CD::CDMatrix2::operator!=(const CDMatrix2 & mat) const
{
	return (m[0] != mat.m[0]) || (m[1] != mat.m[1]) || (m[2] != mat.m[2]) || (m[3] != mat.m[3]);
}

inline float CD::CDMatrix2::operator[](int index) const
{
	return m[index];
}

inline float & CD::CDMatrix2::operator[](int index)
{
	return m[index];
}

inline CD::CDMatrix2 CD::operator-(const CDMatrix2 & mat)
{
	return CDMatrix2(-mat[0], -mat[1], -mat[2], -mat[3]);
}

inline CD::CDMatrix2 CD::operator*(float scalar, const CDMatrix2 & mat)
{
	return CDMatrix2(scalar*mat[0], scalar*mat[1], scalar*mat[2], scalar*mat[3]);
}

inline CD::CDVector2 CD::operator*(const CDVector2 & vec, const CDMatrix2 & mat)
{
	return CDVector2(vec.x*mat[0] + vec.y*mat[2], vec.x*mat[1] + vec.y*mat[3]);
}

inline std::ostream & CD::operator<<(std::ostream & os, const CDMatrix2 & m)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[1] << "]\n"
		<< "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[3] << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}

inline CD::CDMatrix2 CD::transposeMatrix(const CDMatrix2 & mat)
{
	CDMatrix2 trans = mat;
	std::swap(trans.m[1], trans.m[2]);
	return trans;
}

inline CD::CDMatrix2 CD::invertMatrix(const CDMatrix2 & mat)
{
	CDMatrix2 inver = mat;
	float determinant = inver.getDeterminant();
	if (determinant >= -0.00001f&&determinant <= 0.00001f)//if in range 0 return identity matrix
	{
		return inver.identity();
	}
	float tmp = inver.m[0];   // copy the first element for change with the finish element
	float invDeterminant = 1.0f / determinant;
	inver.m[0] = invDeterminant * inver.m[3];
	inver.m[1] *= -invDeterminant;
	inver.m[2] *= -invDeterminant;
	inver.m[3] = invDeterminant * tmp;
	return inver;
}

inline const float * CD::CDMatrix2::get() const
{
	return m;
}

inline float CD::CDMatrix2::getDeterminant()
{
	return m[0] * m[3] - m[1] * m[2];
}

inline CD::CDMatrix2 & CD::CDMatrix2::identity()
{
	m[0] = 1.0f; m[1] = 0.0f;
	m[2] = 0.0f; m[3] = 1.0f;
	return *this;
}

inline CD::CDMatrix2 & CD::CDMatrix2::transpose()
{
	std::swap(m[1], m[2]);
	return *this;
}

inline CD::CDMatrix2 CD::CDMatrix2::getTranspose()
{
	CDMatrix2 trans = *this;
	std::swap(trans.m[1], trans.m[2]);
	return trans;
}

inline CD::CDMatrix2 & CD::CDMatrix2::invert()
{
	float determinant = getDeterminant();
	if (determinant >= -0.00001f&&determinant <= 0.00001f)//if in range 0 return identity matrix
	{
		return identity();
	}
	float tmp = m[0];   // copy the first element for change with the finish element
	float invDeterminant = 1.0f / determinant;
	m[0] = invDeterminant * m[3];
	m[1] *= -invDeterminant;
	m[2] *= -invDeterminant;
	m[3] = invDeterminant * tmp;
	return *this;
}

inline CD::CDMatrix2 CD::CDMatrix2::getInvert()
{
	CDMatrix2 inver = *this;
	float determinant = getDeterminant();
	if (determinant >= -0.00001f&&determinant <= 0.00001f)//if in range 0 return identity matrix
	{
		return inver.identity();
	}
	float tmp = inver.m[0];   // copy the first element for change with the finish element
	float invDeterminant = 1.0f / determinant;
	inver.m[0] = invDeterminant * inver.m[3];
	inver.m[1] *= -invDeterminant;
	inver.m[2] *= -invDeterminant;
	inver.m[3] = invDeterminant * tmp;
	return inver;
}