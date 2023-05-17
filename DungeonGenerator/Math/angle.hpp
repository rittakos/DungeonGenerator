#pragma once

#ifndef ANGLE_H
#define ANGLE_H

#include "math.hpp"


namespace Math
{
	class Angle final
	{
	private:
		float angleInRad;

		void normalise()
		{
			int count = static_cast<int>(floorf(angleInRad / (Math::Constant::Pi * 2)));
			angleInRad -=  count * (2.0f * Math::Constant::Pi);
		}

	public:
		explicit Angle(float angle) : angleInRad (angle) {}

		constexpr Angle() : angleInRad(0) {}

		inline bool		operator==(const Angle& other) const
		{
			return isEqual(this->angleInRad, other.angleInRad);
		}
		inline Angle operator +=(const Angle& other)
		{
			*this = *this + other;
			return *this;
		}
		inline Angle operator -=(const Angle& other)
		{
			*this = *this - other;
			return *this;
		}
		inline bool		operator<(const Angle& other) const
		{
			return this->angleInRad < other.angleInRad;
		}
		inline bool		operator>(const Angle& other) const
		{
			return this->angleInRad > other.angleInRad;
		}
		inline Angle	operator-() const
		{
			return Angle(-1.0f * angleInRad);
		}

		float getDeg() const;
		float getRad() const;

		friend float sin(const Angle& angle);
		friend float cos(const Angle& angle);
		friend float tan(const Angle& angle);


		friend Angle operator+(const Angle& angle1, const Angle& angle2);
		friend Angle operator-(const Angle& angle1, const Angle& angle2);
		friend Angle operator*(const Angle& angle1, const Angle& angle2);
		friend Angle operator*(float skalar, const Angle& angle);
		friend Angle operator*(const Angle& angle, float skalar);
		friend Angle operator/(const Angle& angle1, const Angle& angle2);
		friend Angle operator/(const Angle& angle, float skalar);
	};

	inline Angle operator+(const Angle& angle1, const Angle& angle2)
	{
		Angle res(angle1.angleInRad + angle2.angleInRad);
		//res.normalise();
		return res;
	}

	inline Angle operator-(const Angle& angle1, const Angle& angle2)
	{
		return angle1 + (-1.0f * angle2);
	}

	inline Angle operator*(const Angle& angle1, const Angle& angle2)
	{
		Angle res(angle1.angleInRad * angle2.angleInRad);
		//res.normalise();
		return res;
	}

	inline Angle operator*(float skalar, const Angle& angle)
	{
		Angle res(skalar * angle.angleInRad);
		//res.normalise();
		return res;
	}

	inline Angle operator*(const Angle& angle, float skalar)
	{
		return skalar * angle;
	}

	inline Angle operator/(const Angle& angle1, const Angle& angle2)
	{
		Angle res(angle1.angleInRad / angle2.angleInRad);
		//res.normalise();
		return res;
	}

	inline Angle operator/(const Angle& angle, float skalar)
	{
		Angle res(angle.angleInRad / skalar);
		//res.normalise();
		return res;
	}

	inline float sin(const Angle& angle)
	{
		return sinf(angle.angleInRad);
	}

	inline float cos(const Angle& angle)
	{
		return cosf(angle.angleInRad);
	}

	inline float tan(const Angle& angle)
	{
		return tanf(angle.angleInRad);
	}

	inline Angle asin(float sin)
	{
		return Angle(asinf(sin));
	}
				 
	inline Angle acos(float cos)
	{
		return Angle(acosf(cos));
	}
			 
	inline Angle atan(float tan)
	{
		return Angle(atanf(tan));
	}

	inline Angle AngleFromDeg(float deg)
	{
		return Angle(deg / 180.0f * Constant::Pi);
	}

	inline Angle AngleFromRad(float rad)
	{
		return Angle(rad);
	}
}

inline Math::Angle operator "" _deg(long double degree)
{
	return Math::Angle(static_cast<float>(degree) * Math::Constant::Pi / 180.0f);
}

inline Math::Angle operator "" _rad(long double degree)
{
	return Math::Angle(static_cast<float>(degree));
}


#endif