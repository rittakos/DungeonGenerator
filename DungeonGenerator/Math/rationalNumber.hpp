#pragma once

#include "math.hpp"

namespace Math
{

	class RationalNumber final
	{
	private:
		int numerator;		//szamlalo
		int denominator;	//nevezo

	public:
		RationalNumber(int numerator, int denominator);

		operator float() const;

		//TODO tovabbi operatorok
	};

}