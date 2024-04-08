#include "edge.hpp"
#include "line.hpp"
#include <cmath>

namespace Geometry
{
	Edge::Edge(Math::Vec2f p1, Math::Vec2f p2)
	{
		this->p1 = p1;
		this->p2 = p2;
	}

	Line Edge::convertToLine() const
	{
		return Line(p1, p2);
	}

	Edge::Edge(const Edge& other)
	{
		p1 = other.p1;
		p2 = other.p2;
	}

	Edge& Edge::operator=(const Edge& other)
	{
		p1 = other.p1;
		p2 = other.p2;

		return *this;
	}

	bool Edge::containsPoint(Math::Vec2f p) const
	{
		Geometry::Line l(p1, p2);
		if (!l.containsPoint(p))
			return false;

		return inRange(p);
	}

	bool Edge::inRange(Math::Vec2f p) const
	{
		if (p[0] < std::fmin(p1[0], p2[0]) || p[0] > std::fmax(p1[0], p2[0])) //based on x
			return false;

		if (p[1] < std::fmin(p1[1], p2[1]) || p[1] > std::fmax(p1[1], p2[1])) //based on y (not necessary)
			return false;

		return true;
	}

	std::optional<Math::Vec2f> getIntersectionPoint(const Edge& e1, const Edge& e2)
	{
		std::optional<Math::Vec2f> P = getIntersectionPoint(e1.convertToLine(), e2.convertToLine());

		if (!P.has_value())
			return {};

		if (e1.inRange(P.value()) && e2.inRange(P.value()))
			return P.value();

		return {};
	}

	std::optional<Math::Vec2f> getIntersectionPoint(const Edge& edge, const Line& line)
	{
		Line l2(edge.p1, edge.p2);
		std::optional<Math::Vec2f> p = getIntersectionPoint(line, l2);
		if (p.has_value())
			if (edge.inRange(p.value()))
				return p.value();
		return {};
	}


	bool operator==(const Edge& e1, const Edge& e2)
	{
		return (e1.p1 == e2.p1 && e1.p2 == e2.p2) || (e1.p1 == e2.p2 && e1.p2 == e2.p1);
	}

	bool operator!=(const Edge& e1, const Edge& e2)
	{
		return !(e1 == e2);
	}
}