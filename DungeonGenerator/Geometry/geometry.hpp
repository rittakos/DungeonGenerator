#pragma once

#include <array>

#include "vector.hpp"
#include "edge.hpp"
#include "polygon.hpp"

namespace Geometry
{
	Math::Vec2f calcTriangleOutterCircleCenter(std::array<Math::Vec2f, 3> points);

	std::optional<Geometry::Edge> getCommonEdge(Geometry::Polygon polygon1, Geometry::Polygon polygon2);
}