#pragma once

#include "math.hpp"
#include "vector.hpp"
#include "isAllSame.hpp"

namespace Math
{
	/*template<int X, int Y, VecNumber Type = float>
	using Matrix = Vec<Y, Vec<X, Type>>;*/

	template<int X, int Y, VecNumber Type = float>
	class Mat
	{
		Type coords[X * Y];

		int length;
		int width = X;
		int height = Y;

	public:

		//Constructors
		Mat()
		{
			length = X * Y;

			for (int idx = 0; idx < length; ++idx)
				coords[idx] = 0;
		}

		template<typename ...T>
		explicit Mat(T... args) : Mat()
		{
			static_assert(is_all_same<Type, T...>::value, "Type mismatch!");

			std::vector<Type> vec = { args... };

			if (length != vec.size())
				throw new TooMuchParametersException(/*length, vec.size()*/);

			for (unsigned i = 0; i < vec.size(); ++i) {
				coords[i] = vec[i];
			}
		}

		//template<typename ...>
		explicit Mat(std::initializer_list<Vec<X, Type>> vecs) : Mat()
		{
			//std::vector<Type> vec = { args... };

			if (length != vecs.size())
				throw new TooMuchParametersException(/*length, vec.size()*/);

			for (unsigned i = 0; i < vecs.size(); ++i) {
				coords[i] = vecs[i];
			}
		}

		/*Vec<D, Type>& operator=(const Vec<D, Type>& other)
		{
			for (int idx = 0; idx < D; ++idx)
				this->coords[idx] = other.coords[idx];

			return *this;
		}*/


		//logical operators
	//	bool	operator==(const Vec& other) const
	//	{
	//		for (int idx = 0; idx < D; ++idx)
	//			if (!isEqual(this->coords[idx] - other.coords[idx], 0.0f))
	//				return false;
	//		return true;
	//	}
	//	bool	operator<(const Vec& other) = delete;
	//	bool	operator>(const Vec& other) = delete;

	//	//arithmetic operator
	//	Vec		operator+(const Vec& other) const
	//	{
	//		Vec<D, Type> result;
	//		for (int idx = 0; idx < D; ++idx)
	//			result.coords[idx] = coords[idx] + other[idx];

	//		return result;
	//	}
	//	Vec		operator-(const Vec& other) const
	//	{
	//		return *this + (-1.0 * other);
	//	}
	//	float	operator*(const Vec& other) const
	//	{
	//		float result = 0;
	//		for (int idx = 0; idx < D; ++idx)
	//			result += coords[idx] * other[idx];

	//		return result;
	//	}

	//	//index operator
	//	Type	operator[](int idx) const
	//	{
	//		return coords[idx];
	//	}

	//	/*private:
	//		Type&	operator[](int idx)
	//		{
	//			return coords[idx];
	//		}*/

	//public:


	//	//other functions
	//	float	length() const
	//	{
	//		float sum = 0;
	//		for (int idx = 0; idx < D; ++idx)
	//			sum += coords[idx] * coords[idx];

	//		return sqrtf(sum);
	//	}
	//	void	normalise()
	//	{
	//		*this = *this / this->length();
	//	}

	//	Vec		getNormalised() const
	//	{
	//		return *this / this->length();
	//	}

	//	Angle	angleWith(const Vec& other) const
	//	{
	//		float cosAngle = ((*this) * other) / (length() * other.length());
	//		Angle angle = Angle(acosf(cosAngle));
	//		return angle;
	//	}


		//external operators
		template<int X1, int Y1, class Type1 >	friend std::ostream& operator<<(std::ostream& os, const Mat<X1, Y1, Type1>& m);
		template<int D1, class Type1 >	friend std::istream& operator>>(std::istream& is, Vec<D1, Type1>& vec);
		template<int D1, class Type1 >	friend Vec<D1, Type1>	operator*(const Vec<D1, Type1>& vec, float skalar);
		template<int D1, class Type1 >	friend Vec<D1, Type1>	operator*(float skalar, const Vec<D1, Type1>& vec);
		template<int D1, class Type1 >	friend Vec<D1, Type1>	operator/(const Vec<D1, Type1>& vec, float skalar);
	};

	template<int X1, int Y1, class Type1 >
	std::ostream& operator<<(std::ostream& os, const Mat<X1, Y1, Type1>& m)
	{
		for (int y = 0; y < m.height; ++y)
		{
			for (int x = 0; x < m.width; ++x)
			{
				os << m.coords[y * m.width + x] << "\t";
			}
			os << std::endl;
		}
		return os;
	}

}