#pragma once
#include <cmath>
#include <iostream>
#include "CDVector2.h"
#include "CDVector3.h"
namespace CD
{
	///////////////////////////////////////////////////////////////////////////////
	// CDVector4
	///////////////////////////////////////////////////////////////////////////////
	struct CDVector4
	{
		union
		{
			struct
			{
				float X, Y, Z, W;
			};
			struct
			{
				float a, b, c, d;
			};
			struct
			{
				float x, y, z, w;
			};
			struct
			{
				float r, g, b, a;
			};
			struct
			{
				float R, G, B, A;
			};
			float Vector[4];
		};

		// ctors
		CDVector4() : x(0), y(0), z(0), w(0) {};
		CDVector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {};
		CDVector4(float _xy[2], float _z, float _w) : x(_xy[0]), y(_xy[1]), z(_z), w(_w) {};
		CDVector4(float _x, float _yz[2], float _w) : x(_x), y(_yz[0]), z(_yz[1]), w(_w) {};
		CDVector4(float _x, float _y, float _zw[2]) : x(_x), y(_y), z(_zw[0]), w(_zw[1]) {};
		CDVector4(float _xy[2], float _zw[2]) : x(_xy[0]), y(_xy[1]), z(_zw[0]), w(_zw[1]) {};
		CDVector4(float _xyz[3], float _w) : x(_xyz[0]), y(_xyz[1]), z(_xyz[2]), w(_w) {};
		CDVector4(float _x, float _yzw[3]) : x(_x), y(_yzw[0]), z(_yzw[1]), w(_yzw[2]) {};
		CDVector4(float _xyzw[4]) : x(_xyzw[0]), y(_xyzw[1]), z(_xyzw[2]), w(_xyzw[3]) {};
		CDVector4(const CDVector2& _xy, float _z, float _w) : x(_xy.x), y(_xy.y), z(_z), w(_w) {};
		CDVector4(const CDVector2& _xy, float _zw[2]) : x(_xy.x), y(_xy.y), z(_zw[0]), w(_zw[1]) {};
		CDVector4(float _x, const CDVector2& _yz, float _w) : x(_x), y(_yz.x), z(_yz.y), w(_w) {};
		CDVector4(float _x, float _y, const CDVector2& _zw) : x(_x), y(_y), z(_zw.x), w(_zw.y) {};
		CDVector4(float _xy[2], const CDVector2& _zw) : x(_xy[0]), y(_xy[1]), z(_zw.x), w(_zw.y) {};
		CDVector4(const CDVector2& _xy, const CDVector2& _zw) : x(_xy.x), y(_xy.y), z(_zw.x), w(_zw.y) {};
		CDVector4(const CDVector3& _xyz, float _w) : x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w) {};
		CDVector4(float _x, const CDVector3& _yzw) : x(_x), y(_yzw.x), z(_yzw.y), w(_yzw.z) {};

		// utils functions
		void		set(float _x, float _y, float _z, float _w);
		float		length() const;								//
		float       squareLength() const;						//
		float       distance(const CDVector4& vec) const;		// distance between two vectors
		CDVector4&  normalize();								// tranform this vector in your' s normalize
		CDVector4   getnormalize();								// return de normalize version of this vector
		float       dot(const CDVector4& vec) const;			// dot product
		CDVector4   cross(const CDVector4& vec) const;			// dot product
		bool        equal(const CDVector4& vec, float e) const; // compare with epsilon

		static float		dot(const CDVector4& vec1, const CDVector4& vec2);				// dot product
		static CDVector4	cross(const CDVector4& vec1, const CDVector4& vec2);			// cross product
		static CDVector4    vectorResult(const CDVector4& init, const CDVector4& finish);	// distance between two vectors
		static float		length(const CDVector4& vec);									//
		static float		squareLength(const CDVector4& vec);								//
		static float		distance(const CDVector4& veci, const CDVector4& vecf);			// distance between two vectors
		static CDVector4	normalize(const CDVector4& vec);								//
		// operators
		CDVector4     operator-() const;						// unary operator (negate)
		CDVector4     operator+(const CDVector4& vec) const;    // add rhs
		CDVector4     operator-(const CDVector4& vec) const;    // subtract rhs
		CDVector4&    operator+=(const CDVector4& vec);         // add rhs and update this object
		CDVector4&    operator-=(const CDVector4& vec);         // subtract rhs and update this object
		CDVector4     operator*(const float scale) const;		// scale
		CDVector4     operator*(const CDVector4& vec) const;    // multiply each element
		CDVector4&    operator*=(const float scale);			// scale and update this object
		CDVector4&    operator*=(const CDVector4& vec);         // multiply each element and update this object
		CDVector4     operator/(const float scale) const;		// inverse scale
		CDVector4&    operator/=(const float scale);			// scale and update this object
		bool        operator==(const CDVector4& vec) const;		// exact compare, no epsilon
		bool        operator!=(const CDVector4& vec) const;		// exact compare, no epsilon
		bool        operator<(const CDVector4& vec) const;		// comparison for sort
		float       operator[](int index) const;				// subscript operator v[0], v[1]
		float&      operator[](int index);						// subscript operator v[0], v[1]
		CDVector4&    operator=(const CDVector4& vec);

		friend CDVector4 operator*(const float a, const CDVector4 vec);
		friend std::ostream& operator<<(std::ostream& os, const CDVector4& vec);
	};

	inline CD::CDVector4 CD::CDVector4::operator-() const
	{
		return CDVector4(-x, -y, -z, -w);
	}

	inline CD::CDVector4 CD::CDVector4::operator+(const CDVector4 & vec) const
	{
		return CDVector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	inline CD::CDVector4 CD::CDVector4::operator-(const CDVector4 & vec) const
	{
		return CDVector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}

	inline CD::CDVector4 & CD::CDVector4::operator+=(const CDVector4 & vec)
	{
		x += vec.x; y += vec.y; z += vec.z; w += vec.w;
		return *this;
	}

	inline CD::CDVector4 & CD::CDVector4::operator-=(const CDVector4 & vec)
	{
		x -= vec.x; y -= vec.y; z -= vec.z; w -= vec.w;
		return *this;
	}

	inline CD::CDVector4 CD::CDVector4::operator*(const float scale) const
	{
		return CDVector4(X*scale, y*scale, z*scale, w*scale);
	}

	inline CD::CDVector4 CD::CDVector4::operator*(const CDVector4 & vec) const
	{
		return CDVector4(X*vec.x, y*vec.y, z*vec.z, w*vec.w);
	}

	inline CD::CDVector4 & CD::CDVector4::operator*=(const float scale)
	{
		x *= scale; y *= scale; z *= scale; w *= scale;
		return *this;
	}

	inline CD::CDVector4 & CD::CDVector4::operator*=(const CDVector4 & vec)
	{
		x *= vec.x; y *= vec.y; z *= vec.z; w *= vec.w;
		return *this;
	}

	inline CD::CDVector4 CD::CDVector4::operator/(const float scale) const
	{
		return CDVector4(X / scale, y / scale, z / scale, w / scale);
	}

	inline CD::CDVector4 & CD::CDVector4::operator/=(const float scale)
	{
		x /= scale; y /= scale; z /= scale; w /= scale;
		return *this;
	}

	inline bool CD::CDVector4::operator==(const CDVector4 & vec) const
	{
		return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w);
	}

	inline bool CD::CDVector4::operator!=(const CDVector4 & vec) const
	{
		return (x != vec.x) || (y != vec.y) || (z != vec.z) || (w != vec.w);
	}

	inline bool CD::CDVector4::operator<(const CDVector4 & vec) const
	{
		if (x < vec.x) return true;
		if (x > vec.x) return false;
		if (y < vec.y) return true;
		if (y > vec.y) return false;
		if (z < vec.z) return true;
		if (z > vec.z) return false;
		if (w < vec.w) return true;
		if (w > vec.w) return false;
		return false;
	}

	inline float CD::CDVector4::operator[](int index) const
	{
		return (&x)[index];
	}

	inline float & CD::CDVector4::operator[](int index)
	{
		return (&x)[index];
	}

	inline CD::CDVector4 & CD::CDVector4::operator=(const CDVector4 & vec)
	{
		x = vec.x; y = vec.y; z = vec.z; w = vec.w;
		return *this;
	}

	inline CD::CDVector4 CD::operator*(const float a, const CDVector4 vec)
	{
		return CDVector4(a*vec.x, a*vec.y, a*vec.z, a*vec.w);
	}

	inline std::ostream & CD::operator<<(std::ostream & os, const CDVector4 & vec)
	{
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
		return os;
	}

	inline void CD::CDVector4::set(float _x, float _y, float _z, float _w)
	{
		this->x = _x; this->y = _y; this->z = _z; this->w = _w;
	}

	inline float CD::CDVector4::length() const
	{
		return sqrtf(x*x + y * y + z * z + w * w);
	}

	inline float CD::CDVector4::squareLength() const
	{
		return (x*x + y * y + z * z + w * w);
	}

	inline float CD::CDVector4::distance(const CDVector4 & vec) const
	{
		return sqrtf((vec.x - x)*(vec.x - x) + (vec.y - y)*(vec.y - y) + (vec.z - z)*(vec.z - z) + (vec.w - w)*(vec.w - w));
	}

	inline CD::CDVector4 CD::CDVector4::vectorResult(const CDVector4 & init, const CDVector4 & finish)
	{
		return CDVector4(finish - init);
	}

	inline float CDVector4::length(const CDVector4 & vec)
	{
		return sqrtf(vec.x*vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
	}

	inline float CDVector4::squareLength(const CDVector4 & vec)
	{
		return (vec.x*vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
	}

	inline float CDVector4::distance(const CDVector4 & veci, const CDVector4 & vecf)
	{
		return sqrtf((vecf.x - veci.x)*(vecf.x - veci.x) + (vecf.y - veci.y)*(vecf.y - veci.y) + (vecf.z - veci.z)*(vecf.z - veci.z) + (vecf.w - veci.w)*(vecf.w - veci.w));

	}

	inline CDVector4 CDVector4::normalize(const CDVector4 & vec)
	{
		CDVector4 result;
		float mod = squareLength(vec);
		if (mod == 0)
		{
			result.x = 0;
			result.y = 0;
			result.z = 0;
			result.w = 0;
		}
		else
		{
			float invLength = 1.0f / sqrtf(mod);
			result.x = vec.x*invLength;
			result.y = vec.y*invLength;
			result.z = vec.z*invLength;
			result.w = vec.w*invLength;
		}
		return result;
	}

	inline CD::CDVector4 & CD::CDVector4::normalize()
	{
		//NOTE: leave w-component untouched
		//@@const float EPSILON = 0.000001f;
		float mod = squareLength();
		if (mod==0)
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
		else
		{
			float invLength = 1.0f / sqrtf(mod);
			x *= invLength;
			y *= invLength;
			z *= invLength;
			w *= invLength;
		}
		return *this;
	}

	inline CDVector4 CDVector4::getnormalize()
	{
		CDVector4 result=*this;
		float mod = squareLength();
		if (mod==0)
		{
			result.x = 0;
			result.y = 0;
			result.z = 0;
			result.w = 0;
		}
		else
		{
			float invLength = 1.0f / sqrtf(mod);
			result.x *= invLength;
			result.y *= invLength;
			result.z *= invLength;
			result.w *= invLength;
		}
		return result;
	}

	inline float CD::CDVector4::dot(const CDVector4 & vec) const
	{
		return (x*vec.x + y * vec.y + z * vec.z + w * vec.w);
	}

	inline CDVector4 CDVector4::cross(const CDVector4 & vec) const
	{
		return 	CDVector4((y * vec[2] - z * vec[1]), (x * vec[2] - z * vec[0]), (x * vec[1] - y * vec[0]),0.0f);
	}

	inline bool CD::CDVector4::equal(const CDVector4 & vec, float e) const
	{
		return fabs(x - vec.x) < e && fabs(y - vec.y) < e &&
			fabs(z - vec.z) < e && fabs(w - vec.w) < e;
	}
	inline float CDVector4::dot(const CDVector4 & vec1, const CDVector4 & vec2)
	{
		return (vec1.x*vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
	}
	inline CDVector4 CDVector4::cross(const CDVector4 & vec1, const CDVector4 & vec2)
	{
		return 	CDVector4((vec1.y * vec2[2] - vec1.z * vec2[1]), (vec1.z * vec2[0] - vec1.x * vec2[2]), (vec1.x * vec2[1] - vec1.y * vec2[0]), 0.0f);

		return CDVector4();
	}
}