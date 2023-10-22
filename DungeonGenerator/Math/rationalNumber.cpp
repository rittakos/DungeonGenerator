#include "rationalNumber.hpp"
#include "math.hpp"

namespace Math
{
	RationalNumber::RationalNumber(int numerator, int denominator) : numerator(numerator), denominator(denominator)
	{
		if (denominator == 0)
			throw new ZeroDivisionException();
	}

	RationalNumber::operator float() const 
	{ 
		return (float)numerator / (float)denominator; 
	}
}
