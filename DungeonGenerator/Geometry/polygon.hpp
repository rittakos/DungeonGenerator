#pragma once
#include <vector>
#include "line.hpp"
#include "vector.hpp"

namespace Geometry
{
	class Polygon
	{
	private:
		std::vector<Math::Vec2f> points;
		int n;
		bool convex;

		void calculateConvexity ();

	public:
		Polygon() : n(0) { calculateConvexity(); };
		Polygon(std::vector<Math::Vec2f> points);
		Polygon(std::initializer_list<Math::Vec2f> points);

		float	Area() const;
		void	addPoint(Math::Vec2f p);

		bool	isConvex() const { return convex; }

		float	beauty() const;

		friend std::vector<Math::Vec2f> getIntersectionPoints(const Line& line, const Polygon& polygon);
		friend std::vector<Polygon> dividePolygonByLine(const Line& line, const Polygon& polygon);
		friend Math::Vec2f cutPartFromPolygon(Math::Vec2f P, float targerArea, Polygon polygon);
	};

	std::vector<Math::Vec2f> getIntersectionPoints(const Line& line, const Polygon& polygon);
	std::vector<Polygon> dividePolygonByLine(const Line& line, const Polygon& polygon);
	Math::Vec2f cutPartFromPolygon(Math::Vec2f P, float targerArea, Polygon polygon);

}