#pragma once
#include <cmath>
#include <iostream>
#include "CDVector2.h"
namespace CD
{
	///////////////////////////////////////////////////////////////////////////////
	// vector3
	///////////////////////////////////////////////////////////////////////////////
	struct CDVector3
	{
		union
		{
			struct
			{
				float X, Y, Z;
			};
			struct
			{
				float a, b, c;
			};
			struct
			{
				float x, y, z;
			};
			struct
			{
				float r, g, b;
			};
			struct
			{
				float R, G, B;
			};
			float Vector[3];
		};
		// ctors
		CDVector3() : x(0), y(0), z(0) {};
		CDVector3(float x, float y, float z) : x(x), y(y), z(z) {};
		CDVector3(float xy[2], float z) : x(xy[0]), y(xy[1]), z(z) {};
		CDVector3(float x, float yz[2]) : x(x), y(yz[0]), z(yz[1]) {};
		CDVector3(float xyz[3]) : x(xyz[0]), y(xyz[1]), z(xyz[2]) {};
		CDVector3(const CDVector2& xy, float z) : x(xy.x), y(xy.y), z(z) {};
		CDVector3(float x, const CDVector2& yz) : x(x), y(yz.x), z(yz.y) {};
		CDVector3(const CDVector3& vec) : x(vec.x), y(vec.y), z(vec.z) {};

		// utils functions
		void set(float _x, float _y, float _z);
		void set(float _xy[2], float _z) { this->x = _xy[0]; this->y = _xy[1], this->z = _z; };
		void set(float _x, float yz[2]) {this->x = _x; this->y = yz[0]; this->z = (yz[1]);};
		void set(float _xyz[3]) {this->x = _xyz[0]; this->y = _xyz[1]; this->z = _xyz[2];};
		void set(const CDVector2& _xy, float _z) {this->x = _xy.x; this->y = _xy.y;  this->z = _z;};
		void set(float _x, const CDVector2& _yz) { this->x = _x; this->y = _yz.x; this->z = _yz.y;};
		void set(const CDVector3& vec) {this->x = vec.x; this->y = vec.y; this->z = vec.z;};
		float       length() const;								//
		float       squareLength() const;						//
		float       distance(const CDVector3& vec) const;		// distance between two vectors
		CDVector3&  normalize();								//
		CDVector3   getnormalize();								//
		float       dot(const CDVector3& vec) const;			// dot product
		CDVector3   cross(const CDVector3& vec) const;			// cross product
		bool        equal(const CDVector3& vec, float e) const; // compare with epsilon

		static float		dot(const CDVector3& vec1, const CDVector3& vec2);				// dot product
		static CDVector3	cross(const CDVector3& vec1, const CDVector3& vec2);			// cross product
		static CDVector3	vectorResult(const CDVector3& init, const CDVector3& finish);	// distance between two vectors
		static float		length(const CDVector3& vec);									//
		static float		squareLength(const CDVector3& vec);								//
		static float		distance(const CDVector3& veci, const CDVector3& vecf);			// distance between two vectors
		static CDVector3	normalize(const CDVector3& vec);								//
		// operators
		CDVector3     operator-() const;						// unary operator (negate)
		CDVector3     operator+(const CDVector3& Vec) const;    // add vector3
		CDVector3     operator-(const CDVector3& Vec) const;    // subtract vector3
		CDVector3&    operator+=(const CDVector3& Vec);         // add rhs and update this object
		CDVector3&    operator-=(const CDVector3& Vec);         // subtract rhs and update this object
		CDVector3     operator*(const float scale) const;		// scale
		CDVector3     operator*(const CDVector3& Vec) const;    // multiplay each element
		CDVector3&    operator*=(const float scale);			// scale and update this object
		CDVector3&    operator*=(const CDVector3& Vec);         // product each element and update this object
		CDVector3     operator/(const float scale) const;		// inverse scale
		CDVector3&    operator/=(const float scale);			// scale and update this object
		bool        operator==(const CDVector3& Vec) const;		// exact compare, no epsilon
		bool        operator!=(const CDVector3& Vec) const;		// exact compare, no epsilon
		bool        operator<(const CDVector3& Vec) const;		// comparison for sort
		float       operator[](int index) const;				// subscript operator v[0], v[1]
		float&      operator[](int index);						// subscript operator v[0], v[1]
		CDVector3&    operator=(const CDVector3& Vec);

		friend CDVector3 operator*(const float a, const CDVector3 vec);
		friend std::ostream& operator<<(std::ostream& os, const CDVector3& vec);
	};
	inline CD::CDVector3 CD::CDVector3::operator-() const
	{
		return CDVector3(-x, -y, -z);
	}

	inline CD::CDVector3 CD::CDVector3::operator+(const CDVector3 & Vec) const
	{
		return CDVector3(x + Vec.x, y + Vec.y, z + Vec.z);
	}

	inline CD::CDVector3 CD::CDVector3::operator-(const CDVector3 & Vec) const
	{
		return CDVector3(x - Vec.x, y - Vec.y, z - Vec.z);
	}

	inline CD::CDVector3 & CD::CDVector3::operator+=(const CDVector3 & Vec)
	{
		x += Vec.x; y += Vec.y; z += Vec.z;
		return *this;
	}

	inline CD::CDVector3 & CD::CDVector3::operator-=(const CDVector3 & Vec)
	{
		x -= Vec.x; y -= Vec.y; z -= Vec.z;
		return *this;
	}

	inline CD::CDVector3 CD::CDVector3::operator*(const float scale) const
	{
		return CDVector3(x*scale, y*scale, z*scale);
	}

	inline CD::CDVector3 CD::CDVector3::operator*(const CDVector3 & Vec) const
	{
		return CDVector3(x*Vec.x, y*Vec.y, z*Vec.z);
	}

	inline CD::CDVector3 & CD::CDVector3::operator*=(const float scale)
	{
		x *= scale; y *= scale; z *= scale;
		return *this;
	}

	inline CD::CDVector3 & CD::CDVector3::operator*=(const CDVector3 & Vec)
	{
		x *= Vec.x; y *= Vec.y; z *= Vec.z;
		return *this;
	}

	inline CD::CDVector3 CD::CDVector3::operator/(const float scale) const
	{

		return CDVector3(x / scale, y / scale, z / scale);
	}

	inline CD::CDVector3 & CD::CDVector3::operator/=(const float scale)
	{
		x /= scale; y /= scale; z /= scale;
		return *this;
	}

	inline bool CD::CDVector3::operator==(const CDVector3 & Vec) const
	{
		return (x == Vec.x) && (y == Vec.y) && (z == Vec.z);
	}

	inline bool CD::CDVector3::operator!=(const CDVector3 & Vec) const
	{
		return (x != Vec.x) || (y != Vec.y) || (z != Vec.z);
	}

	inline bool CD::CDVector3::operator<(const CDVector3 & Vec) const
	{
		if (x < Vec.x) return true;
		if (y < Vec.y) return true;
		if (z < Vec.z) return true;
		return false;
	}

	inline float CD::CDVector3::operator[](int index) const
	{
		return (&x)[index];
	}

	inline float & CD::CDVector3::operator[](int index)
	{
		return (&x)[index];
	}

	inline CD::CDVector3 & CD::CDVector3::operator=(const CDVector3 & Vec)
	{
		x = Vec.x; y = Vec.y; z = Vec.z;
		return *this;
	}

	inline CD::CDVector3 CD::operator*(const float a, const CDVector3 vec)
	{
		return CDVector3(a*vec.x, a*vec.y, a*vec.z);
	}

	inline std::ostream & CD::operator<<(std::ostream & os, const CDVector3 & vec)
	{
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}

	inline void CD::CDVector3::set(float _x, float _y, float _z)
	{
		this->x = _x; this->y = _y; this->z = _z;
	}

	inline float CD::CDVector3::length() const
	{
		return sqrtf(x*x + y * y + z * z);
	}

	inline float CD::CDVector3::squareLength() const
	{
		return (x*x + y * y + z * z);
	}

	inline float CD::CDVector3::distance(const CDVector3 & vec) const
	{
		return sqrtf((vec.x - x)*(vec.x - x) + (vec.y - y)*(vec.y - y) + (vec.z - z)*(vec.z - z));
	}

	inline CD::CDVector3 CD::CDVector3::vectorResult(const CDVector3 & init, const CDVector3 & finish)
	{
		return CDVector3(finish - init);
	}

	inline float CDVector3::length(const CDVector3 & vec)
	{
		return sqrtf(vec.x*vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	inline float CDVector3::squareLength(const CDVector3 & vec)
	{
		return (vec.x*vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	inline float CDVector3::distance(const CDVector3 & veci, const CDVector3 & vecf)
	{
		return sqrtf((vecf.x - veci.x)*(vecf.x - veci.x) + (vecf.y - veci.y)*(vecf.y - veci.y) + (vecf.z - veci.z)*(vecf.z - veci.z));

	}

	inline CDVector3 CDVector3::normalize(const CDVector3 & vec)
	{
		CDVector3 result;
		float mod = squareLength(vec);
		float invLength = 1.0f / sqrtf(mod);
		result.x = vec.x*invLength;
		result.y = vec.y*invLength;
		result.z = vec.z*invLength;
		return result;
	}

	inline CD::CDVector3 & CD::CDVector3::normalize()
	{
		float mod = squareLength();
		float invLength = 1.0f / sqrtf(mod);
		x *= invLength;
		y *= invLength;
		z *= invLength;
		return *this;
	}

	inline CDVector3 CDVector3::getnormalize()
	{
		CDVector3 result;
		float mod = squareLength();
		float invLength = 1.0f / sqrtf(mod);
		result.x = x*invLength;
		result.y = y*invLength;
		result.z = z*invLength;
		return result;
	}

	inline float CD::CDVector3::dot(const CDVector3 & vec) const
	{
		return (x*vec.x + y * vec.y + z * vec.z);
	}

	inline CD::CDVector3 CD::CDVector3::cross(const CDVector3 & vec) const
	{
		return CDVector3(y*vec.z - z * vec.y, z*vec.x - x * vec.z, x*vec.y - y * vec.x);
	}

	inline bool CD::CDVector3::equal(const CDVector3 & vec, float e) const
	{
		return fabs(x - vec.x) < e && fabs(y - vec.y) < e && fabs(z - vec.z) < e;
	}

	inline float CDVector3::dot(const CDVector3 & vec1, const CDVector3 & vec2)
	{
		return (vec1.x*vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
	}

	inline CDVector3 CDVector3::cross(const CDVector3 & vec1, const CDVector3 & vec2)
	{
		return CDVector3(vec1.y*vec2.z - vec1.z * vec2.y, vec1.z*vec2.x - vec1.x * vec2.z, vec1.x*vec2.y - vec1.y * vec2.x);
	}

}