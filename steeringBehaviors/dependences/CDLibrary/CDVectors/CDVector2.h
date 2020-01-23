#pragma once
#include <cmath>
#include <iostream>
namespace CD
{
	///////////////////////////////////////////////////////////////////////////////
	// vector2 
	///////////////////////////////////////////////////////////////////////////////
	struct CDVector2
	{
		union
		{
			struct
			{
				float X, Y;
			};
			struct
			{
				float a, b;
			};
			struct
			{
				float x, y;
			};
			struct
			{
				float r, g;
			};
			struct
			{
				float R, G;
			};
			float Vector[2];
		};

		// ctors
		CDVector2() : x(0), y(0) {};
		CDVector2(float x, float y) : x(x), y(y) {};
		CDVector2(float xy[2]) : x(xy[0]), y(xy[1]) {};
		CDVector2(const CDVector2& vec) : x(vec.x), y(vec.y) {};
		// utils functions
		void        set(float x, float y);
		void        set(float xy[2]);
		void        set(const CDVector2& vec);
		float       length() const;								//
		float       squareLength() const;						//
		float       distance(const CDVector2& vec) const;		// distance between two vectors
		CDVector2&  normalize();								//
		CDVector2	getnormalize();								//
		float       dot(const CDVector2& vec) const;			// dot product
		float       cross(const CDVector2& vec) const;			// cross product
		bool        equal(const CDVector2& vec, float e) const; // compare with epsilon

		static float		dot(const CDVector2& vec1, const CDVector2& vec2);			// dot product
		//static float		cross(const CDVector2& vec1, const CDVector2& vec2);			// cross product
		static CDVector2	vectorResult(const CDVector2& init, const CDVector2& finish);		// vector result between two vectors
		static float		length(const CDVector2& vec);								//
		static float		squareLength(const CDVector2& vec);							//
		static float		distance(const CDVector2& veci, const CDVector2& vecf);		// distance between two vectors
		static CDVector2	normalize(const CDVector2& vec);							//
		 // operators
		CDVector2     operator-() const;						// unary operator (negative)
		CDVector2     operator+(const CDVector2& vec) const;    // add vector2
		CDVector2     operator-(const CDVector2& vec) const;    // subtract vector2
		CDVector2&    operator+=(const CDVector2& vec);         // add vector2 and update this object
		CDVector2&    operator-=(const CDVector2& vec);         // subtract vector2 and update this object
		CDVector2     operator*(const float scale) const;		// scale
		CDVector2     operator*(const CDVector2& vec) const;    // multiply each element
		CDVector2&    operator*=(const float scale);			// scale and update this object
		CDVector2&    operator*=(const CDVector2& vec);         // multiply each element and update this object
		CDVector2     operator/(const float scale) const;		// inverse scale
		CDVector2&    operator/=(const float scale);			// scale and update this object
		bool        operator==(const CDVector2& vec) const;		// exact compare, no epsilon
		bool        operator!=(const CDVector2& vec) const;		// exact compare, no epsilon
		bool        operator<(const CDVector2& vec) const;		// comparison for sort
		float       operator[](int index) const;				// subscript operator v[0], v[1]
		float&      operator[](int index);						// subscript operator v[0], v[1]
		CDVector2&    operator=(const CDVector2& vec);

		friend CDVector2 operator*(const float a, const CDVector2 vec);
		friend std::ostream& operator<<(std::ostream& os, const CDVector2& vec);
	};
	inline CD::CDVector2 CD::CDVector2::operator-() const
	{
		return CDVector2(-x, -y);
	}

	inline CD::CDVector2 CD::CDVector2::operator+(const CDVector2 & vec) const
	{
		return CDVector2(x + vec.x, y + vec.y);
	}

	inline CD::CDVector2 CD::CDVector2::operator-(const CDVector2 & vec) const
	{
		return CDVector2(x - vec.x, y - vec.y);
	}

	inline CD::CDVector2 & CD::CDVector2::operator+=(const CDVector2 & vec)
	{
		x += vec.x; y += vec.y;
		return *this;
	}

	inline CD::CDVector2 & CD::CDVector2::operator-=(const CDVector2 & vec)
	{
		x -= vec.x; y -= vec.y;
		return *this;
	}

	inline CD::CDVector2 CD::CDVector2::operator*(const float scale) const
	{
		return CDVector2(x*scale, y*scale);
	}

	inline CD::CDVector2 CD::CDVector2::operator*(const CDVector2 & vec) const
	{
		return CDVector2(x*vec.x, y*vec.y);
	}

	inline CD::CDVector2 & CD::CDVector2::operator*=(const float scale)
	{
		x *= scale; y *= scale;
		return *this;
	}

	inline CD::CDVector2 & CD::CDVector2::operator*=(const CDVector2 & vec)
	{
		x *= vec.x; y *= vec.y;
		return *this;
	}

	inline CD::CDVector2 CD::CDVector2::operator/(const float scale) const
	{
		return CDVector2(x / scale, y / scale);
	}

	inline CD::CDVector2 & CD::CDVector2::operator/=(const float scale)
	{
		x /= scale; y /= scale;
		return *this;
	}

	inline bool CD::CDVector2::operator==(const CDVector2 & vec) const
	{
		return (x == vec.x) && (y == vec.y);
	}

	inline bool CD::CDVector2::operator!=(const CDVector2 & vec) const
	{
		return (x != vec.x) || (y != vec.y);
	}

	inline bool CD::CDVector2::operator<(const CDVector2 & vec) const
	{
		if (x < vec.x) return true;
		if (y < vec.y) return true;
		return false;
	}

	inline float CD::CDVector2::operator[](int index) const
	{
		return (&x)[index];
	}

	inline float & CD::CDVector2::operator[](int index)
	{
		return (&x)[index];
	}

	inline CD::CDVector2 & CD::CDVector2::operator=(const CDVector2 & vec)
	{
		x = vec.x; y = vec.y;
		return *this;
	}

	inline void CD::CDVector2::set(float x, float y)
	{
		this->x = x; this->y = y;
	}

	inline void CD::CDVector2::set(const CDVector2 & vec)
	{
		this->x = vec.x; this->y = vec.y;
	}

	inline void CD::CDVector2::set(float xy[2])
	{
		this->x = xy[0]; this->y = xy[1];
	}

	inline float CD::CDVector2::length() const
	{
		return sqrtf(x*x + y * y);
	}

	inline float CD::CDVector2::squareLength() const
	{
		return (x * x + y * y);
	}

	inline float CD::CDVector2::distance(const CDVector2 & vec) const
	{
		return sqrtf((vec.x - x)*(vec.x - x) + (vec.y - y)*(vec.y - y));
	}

	inline CD::CDVector2 CD::CDVector2::vectorResult(const CDVector2 & init, const CDVector2 & finish)
	{
		return finish - init;
	}

	inline float CDVector2::length(const CDVector2 & vec)
	{
		return sqrtf(vec.x*vec.x + vec.y * vec.y);
	}

	inline float CDVector2::squareLength(const CDVector2 & vec)
	{
		return (vec.x*vec.x + vec.y * vec.y);
	}

	inline float CDVector2::distance(const CDVector2 & veci, const CDVector2 & vecf)
	{
		return sqrtf((vecf.x - veci.x)*(vecf.x - veci.x) + (vecf.y - veci.y)*(vecf.y - veci.y));
	}

	inline CDVector2 CDVector2::normalize(const CDVector2 & vec)
	{
		CDVector2 result;
		float mod = squareLength(vec);
		float invLength = 1.0f / sqrtf(mod);
		result.x = vec.x *invLength;
		result.y = vec.y *invLength;
		return result;
	}

	inline CD::CDVector2 & CD::CDVector2::normalize()
	{
		float mod = squareLength();
		float invLength = 1.0f / sqrtf(mod);
		x *= invLength;
		y *= invLength;
		return *this;
	}

	inline CDVector2 CDVector2::getnormalize()
	{
		CDVector2 result;
		float mod = squareLength();
		float invLength = 1.0f / sqrtf(mod);
		result.x = x *invLength;
		result.y = x *invLength;
		return result;
	}

	inline float CD::CDVector2::dot(const CDVector2 & vec) const
	{
		return (x*vec.x + y * vec.y);
	}

	inline float CD::CDVector2::cross(const CDVector2 & vec) const
	{
		return ((x * vec.Y) - (y * vec.X));
	}

	inline bool CD::CDVector2::equal(const CDVector2 & vec, float e) const
	{
		return fabs(x - vec.x) < e && fabs(y - vec.y) < e;
	}

	inline float CDVector2::dot(const CDVector2 & vec1, const CDVector2 & vec2)
	{
		return (vec1.x*vec2.x + vec1.y * vec2.y);
	}

	inline CD::CDVector2 CD::operator*(const float a, const CDVector2 vec)
	{
		return CDVector2(a*vec.x, a*vec.y);
	}

	inline std::ostream & CD::operator<<(std::ostream & os, const CDVector2 & vec)
	{
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}
}