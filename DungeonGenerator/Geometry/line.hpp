#pragma once
//#include "vector.hpp"
#include <iostream>
#include "vector.hpp"
#include <optional>

#include "equationSystem.hpp"

namespace Geometry
{
	class Line final
	{
	private:
		Math::Vec2f P1;
		Math::Vec2f P2;
		Math::Vec2f normal;
		Math::Vec2f v;

		Math::LinearEquation<2> lineEquation;

	public:
		Line(const Math::Vec2f& P1, const Math::Vec2f& P2);

		bool containsPoint(const Math::Vec2f& P) const;

		Math::Vec2f getNormal(/*const Math::Vec3f& at*/) const;
		Math::Vec2f getPointAtX(float x) const;
		Math::Vec2f getPointAtY(float y) const;

		Math::LinearEquation<2> getEquation() const { return lineEquation; }

		friend std::optional<Math::Vec2f> getIntersectionPoint(const Line& l1, const Line& l2);
		friend bool operator==(const Line& l1, const Line& l2);
	};

	std::optional<Math::Vec2f> getIntersectionPoint(const Line& l1, const Line& l2);

	bool operator==(const Line& l1, const Line& l2);

	Line getBisector(Math::Vec2f P1, Math::Vec2f P2);
}