#include "line.hpp"

#include "transformation.hpp"


namespace Geometry
{
	Line::Line(const Math::Vec2f& P1, const Math::Vec2f& P2) : P1(P1), P2(P2)
	{
		v = P1 - P2;
		normal = rotate(v, 90.0_deg);
		
		lineEquation = Math::LinearEquation<2>(v[1] * P1[0] - v[0] * P1[1], {v[1], -v[0]});
	}

	bool Line::containsPoint(const Math::Vec2f& P) const
	{
		return lineEquation.isSolution({ P[0], P[1] });
	}


	Math::Vec2f Line::getNormal(/*const Math::Vec2f& at*/) const
	{
		return normal;
	}


	Math::Vec2f Line::getPointAtX(float x) const
	{
		return Math::Vec2f();
	}


	Math::Vec2f Line::getPointAtY(float y) const
	{
		return Math::Vec2f();
	}


	std::optional<Math::Vec2f> getIntersectionPoint(const Line& l1, const Line& l2)
	{
		if(	l1.getNormal().getNormalised() == l2.getNormal().getNormalised() ||
			l1.getNormal().getNormalised() == - 1.0f * l2.getNormal().getNormalised()) //paralell
			return {};

		Math::LinearEquationSystem<2> les;

		les.addLinearEquation(l1.getEquation());
		les.addLinearEquation(l2.getEquation());

		les.solve();
		std::optional<std::vector<float>> intersection = les.getSolution();
		if(intersection.has_value())
			return Math::Vec2f(intersection.value()[0], intersection.value()[1]);
		return {};
	}

	bool operator==(const Line& l1, const Line& l2)
	{
		if (l1.v == l2.v && l1.normal == l2.normal && l1.containsPoint(l2.P1))
			return true;
		return false;
	}

	Line getBisector(Math::Vec2f P1, Math::Vec2f P2)
	{
		Math::Vec2f bisectorVector = Geometry::rotate (P1 - P2, 90.0_deg);
		Math::Vec2f H = (P1 + P2) / 2.0f;
		return Line(H, H + bisectorVector);
	}
}