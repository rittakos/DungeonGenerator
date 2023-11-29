#ifndef VECTOR_HPP
#define VECTOR_HPP

#pragma once
#include <iostream>
#include <cstdarg>
#include <vector>
#include <concepts>

#include "math.hpp"
#include "angle.hpp"
#include "isAllSame.hpp"

namespace Math
{
	template<int D, class Type = float> requires VecNumber<Type>
	class Vec;

	using Vec3i = Vec<3, int>;
	using Vec3f = Vec<3, float>;
	using Vec2f = Vec<2, float>;
	using Vec2i = Vec<2, int>;

	/*template <>
	class Vec<3, float>
	{

	};*/

	template<int D, class Type> requires VecNumber<Type>
	class Vec final
	{
		Type coords[D];

	public:

		//Constructors
		Vec()
		{
			for(int idx = 0; idx < D; ++idx)
				coords[idx] = (Type) 0;
		}

		template<typename ...T>
		explicit Vec(T... args)
		{
			static_assert(is_all_same<Type, T...>::value, "Type mismatch!");

			std::vector<Type> vec = { args... };

			if (vec.size() != D)
				throw new TooMuchParametersException(/*D, vec.size()*/);

			for (unsigned i = 0; i < vec.size(); ++i) {
				coords[i] = vec[i];
			}
		}

		/*Vec<D, Type>& operator=(const Vec<D, Type>& other)
		{
			for (int idx = 0; idx < D; ++idx)
				this->coords[idx] = other.coords[idx];

			return *this;
		}*/


		//logical operators
		bool	operator==(const Vec& other) const
		{
			return equals(*this, other, Math::Constant::epsilon);
		}
		bool	operator<(const Vec& other) = delete;
		bool	operator>(const Vec& other) = delete;

		//arithmetic operator
		Vec		operator+(const Vec& other) const
		{
			Vec<D, Type> result;
			for (int idx = 0; idx < D; ++idx)
				result.coords[idx] = coords[idx] + other[idx];

			return result;
		}

		Vec&	operator+=(const Vec& other)
		{
			*this = *this + other;
			return *this;
		}

		Vec& operator-=(const Vec& other)
		{
			*this = *this - other;
			return *this;
		}

		Vec& operator/=(float other)
		{
			*this = *this / other;
			return *this;
		}

		Vec		operator-(const Vec& other) const
		{
			return *this + (-1.0 * other);
		}

		Vec		operator-() const
		{
			return (* this * -1.0f);
		}

		float	operator*(const Vec& other) const
		{
			float result = 0;
			for (int idx = 0; idx < D; ++idx)
				result += coords[idx] * other[idx];

			return result;
		}

		//index operator
		Type	operator[](int idx) const
		{
			return coords[idx];
		}

		Type&	operator[](int idx)
		{
			return coords[idx];
		}

	public:


		//other functions
		float			length() const 
		{
			float sum = 0;
			for (int idx = 0; idx < D; ++idx)
				sum += coords[idx] * coords[idx];

			return sqrtf(sum);
		}
		void			normalise()
		{
			*this = *this / this->length();
		}
		Vec				getNormalised() const
		{
			return *this / this->length();
		}
		Angle			angleWith(const Vec& other) const
		{
			float cosAngle = ((*this) * other) / (length() * other.length());
			Angle angle = Angle(acosf(cosAngle));
			return angle;
		}

		//external operators
		template<int D1, class Type1 >	friend std::ostream&	operator<<(std::ostream& os, const Vec<D1, Type1>& vec);
		template<int D1, class Type1 >	friend std::istream&	operator>>(std::istream& is, Vec<D1, Type1>& vec);
		template<int D1, class Type1 >	friend Vec<D1, Type1>	operator*(const Vec<D1, Type1>& vec, float skalar);
		template<int D1, class Type1 >	friend Vec<D1, Type1>	operator*(float skalar, const Vec<D1, Type1>& vec);
		template<int D1, class Type1 >	friend Vec<D1, Type1>	operator/(const Vec<D1, Type1>& vec, float skalar);
		template<int D1, class Type1 >	friend bool equals(const Vec<D1, Type1>& v1, const Vec<D1, Type1>& v2, float epsilon);
	};


	template<int D, class Type > 
	inline std::ostream& operator<<(std::ostream& os, const Vec<D, Type>& vec) 
	{
		for (int idx = 0; idx < D - 1; ++idx)
			os << vec.coords[idx] << "\t";
		os << vec.coords[D - 1];

		return os;
	}


	template<int D, class Type>
	std::istream& operator>>(std::istream& is, Vec<D, Type>& vec)
	{
		float coord;
		for (int idx = 0; idx < D; ++idx)
		{
			is >> coord;
			vec.coords[idx] = coord;
		}
			
		return is;
	}


	template<int D1, class Type1>
	Vec<D1, Type1> operator*(const Vec<D1, Type1>& vec, float skalar)
	{
		Vec<D1, Type1> result = vec;
		for (int idx = 0; idx < D1; ++idx)
			result.coords[idx] = vec[idx] * skalar;

		return result;
	}


	template<int D1, class Type1>
	Vec<D1, Type1> operator*(float skalar, const Vec<D1, Type1>& vec)
	{
		return vec * skalar;
	}


	template<int D1, class Type1>
	Vec<D1, Type1> operator/(const Vec<D1, Type1>& vec, float skalar)
	{
		if (skalar == 0.0f)
			throw new ZeroDivisionException();
		return vec * (1.0f / skalar);
	}

	template<int D1, class Type1>
	float distance(const Vec<D1, Type1>& v1, const Vec<D1, Type1>& v2)
	{
		return (v1 - v2).length();
	}

	template<int D1, class Type1>
	bool equals(const Vec<D1, Type1>& v1, const Vec<D1, Type1>& v2, float epsilon)
	{
		for (int idx = 0; idx < D1; ++idx)
			if (!isEqual(v1.coords[idx], v2.coords[idx], epsilon))
				return false;
		return (v1 - v2).length() < epsilon;
	}

	namespace Constant
	{
		const Vec3f	x			(1.0f, 0.0f, 0.0f);
		const Vec3f	y			(0.0f, 1.0f, 0.0f);
		const Vec3f	z			(0.0f, 0.0f, 1.0f);
	}


	Angle getAngle(Vec2f P1, Vec2f P2, Vec2f P3); //bigger angle if counterclockwise, smaller if clockwise

} //namespace Math

#endif