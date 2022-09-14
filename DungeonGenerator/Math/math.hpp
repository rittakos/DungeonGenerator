#pragma once
#include <math.h>
#include <concepts>
#include <exception>

namespace Math
{
	namespace Constant
	{
		const float epsilon =	0.000001f;
		const float Pi		=	3.141592653589793238462643383276f;
	}

	static bool isEqual(float f1, float f2)
	{
		return fabs(f1 - f2) < Constant::epsilon;
	}

	class TooMuchParametersException : std::exception
	{
		/*int expectedCount;
		int currentCount;
	public:
		TooMuchParametersException(int expectedCount, int currentCount)
		{
			this->expectedCount = expectedCount;
			this->currentCount = currentCount;
		}

		const char* what() const throw ()
		{
			std::string what = "Too much arguments. You need to pass " + expectedCount;
			what += "parameters, insted of " + currentCount;
			what += "!!";

			return what.c_str();
		}*/
	};

	class ZeroDevisionException : public std::exception
	{

	};

	template<typename T>
	concept VecNumber = std::floating_point<T> || std::integral<T>;
}