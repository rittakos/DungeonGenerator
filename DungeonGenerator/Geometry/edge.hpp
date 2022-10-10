#pragma once
#include <optional>
#include <vector.hpp>
#include "line.hpp"
#include "edge.hpp"

namespace Geometry
{

	class Edge
	{
	private:
		Math::Vec2f p1;
		Math::Vec2f p2;

	public:
		Edge() = default;
		Edge(Math::Vec2f p1, Math::Vec2f p2);

		bool containsPoint(Math::Vec2f p) const;
		std::optional<Math::Vec2f> getIntersectionPoint(const Edge& other) const;
		std::optional<Math::Vec2f> getIntersectionPoint(const Line& line) const;

	};

}