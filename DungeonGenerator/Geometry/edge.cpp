#include "edge.hpp"

namespace Geometry
{
	Edge::Edge(Math::Vec2f p1, Math::Vec2f p2)
	{

	}

	bool Edge::containsPoint(Math::Vec2f p) const
	{
		return true;
	}

	std::optional<Math::Vec2f> Edge::getIntersectionPoint(const Edge& other) const
	{
		return {};
	}


	std::optional<Math::Vec2f> Edge::getIntersectionPoint(const Line& line) const
	{
		return {};
	}
}