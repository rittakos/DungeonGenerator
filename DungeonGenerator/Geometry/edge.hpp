#pragma once
#include <optional>
#include <vector.hpp>
#include "line.hpp"

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
		
		Edge(const Edge& other);
		Edge& operator=(const Edge& other);

		Line convertToLine() const;

		bool containsPoint(Math::Vec2f p) const;
		bool inRange(Math::Vec2f p) const;

		std::array<Math::Vec2f, 2> getPoints() const { return{ p1, p2 }; }
		
		friend std::optional<Math::Vec2f> getIntersectionPoint(const Edge& e1, const Edge& e2);
		friend std::optional<Math::Vec2f> getIntersectionPoint(const Edge& edge, const Line& line);
		friend bool operator==(const Edge& e1, const Edge& e2);
		friend bool operator!=(const Edge& e1, const Edge& e2);

	};

	bool operator==(const Edge& e1, const Edge& e2);
	bool operator!=(const Edge& e1, const Edge& e2);

	std::optional<Math::Vec2f> getIntersectionPoint(const Edge& e1, const Edge& e2);

	std::optional<Math::Vec2f> getIntersectionPoint(const Edge& edge, const Line& line);

}