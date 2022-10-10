#include "line.hpp"

#include "transformation.hpp"


namespace Geometry
{
	Line::Line(const Math::Vec2f& P1, const Math::Vec2f& P2) : P1(P1), P2(P2)
	{
		v = P1 - P2;
		//normal = rotate(v, 90.0_deg);
		
		lineEquation = Math::LinearEquation<2>(v[1] * P1[0] - v[0] * P1[1], {v[1], -v[0]});
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
		std::vector<float> intersection = les.getSolution();

		return Math::Vec2f(intersection[0], intersection[1]);
	}
}