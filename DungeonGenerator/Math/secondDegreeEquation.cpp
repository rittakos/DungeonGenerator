#include "secondDegreeEquation.hpp"

namespace Math
{

	// a*x^2 + b*x + c = 0
	Math::SecondDegreeEquation::SecondDegreeEquation(float a, float b, float c) 
		: a(a), b(b), c(c)
	{
	}

	std::optional<Math::Vec2f> Math::SecondDegreeEquation::getSolution() const
	{
		//x1/2 = (-b +- sqrt(b^2 - 4ac)) / (2a)
		float D = b * b - 4.0f * a * c;
		if (D < 0)
			return {};

		float x1 = (-b + std::sqrtf(D)) / (2.0f * a);
		float x2 = (-b - std::sqrtf(D)) / (2.0f * a);

		return Vec2f(x1, x2);
	}

}
