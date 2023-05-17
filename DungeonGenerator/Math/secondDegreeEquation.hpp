#pragma once

#include "vector.hpp"
#include <optional>

namespace Math
{
	class SecondDegreeEquation
	{
	private:
		float a;
		float b;
		float c;

	public:
		SecondDegreeEquation(float a, float b, float c);
		std::optional<Math::Vec2f> getSolution() const;
	};
}