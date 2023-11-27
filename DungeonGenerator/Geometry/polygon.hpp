#pragma once
#include <vector>
#include "line.hpp"
#include "vector.hpp"
#include "edge.hpp"

namespace Geometry
{
	class Polygon
	{
	private:
		std::vector<Math::Vec2f> points;
		std::vector<Edge> edges;
		int n;
		bool convex;

		std::vector<Polygon> holes;

		void calculateConvexity ();
		void addEdges();

	public:
		Polygon() : n(0) { calculateConvexity(); };
		Polygon(std::vector<Math::Vec2f> points);
		Polygon(std::initializer_list<Math::Vec2f> points);

		std::vector<Math::Vec2f>	getPoints() const { return points; }
		std::vector<Edge>			getEdges() const { return edges; }

		float	Area() const;
		void	addPoint(Math::Vec2f p);

		bool					addHole(const Polygon& hole);
		std::vector<Polygon>	getHoles() const { return holes; }

		bool	isPointInside(const Math::Vec2f& point) const;
		bool	isConvex() const { return convex; }
		bool	exists() const;
		bool	containsPoint(const Math::Vec2f& P) const;
		
		Math::Angle calcInnerAngle() const { return ((float)(n - 2)) * 180.0_deg; }

		float	beauty() const { return 0.0f; /*TODO beuty szamitas, nem biztos, hogy szukseges mar*/ }

		friend std::vector<Math::Vec2f> getIntersectionPoints(const Line& line, const Polygon& polygon);
		friend std::vector<Polygon> dividePolygonByLine(const Line& line, const Polygon& polygon);
		friend Math::Vec2f cutPartFromPolygon(Math::Vec2f P, float targerArea, Polygon polygon);
		friend std::ostream& operator<<(std::ostream& os, const Polygon& polygon);
		friend bool operator==(const Polygon& polygon1, const Polygon& polygon2);
		friend bool operator!=(const Polygon& polygon1, const Polygon& polygon2);
	};

	std::vector<Math::Vec2f> getIntersectionPoints(const Line& line, const Polygon& polygon);
	std::vector<Polygon> dividePolygonByLine(const Line& line, const Polygon& polygon);
	Math::Vec2f cutPartFromPolygon(Math::Vec2f P, float targerArea, Polygon polygon);

	//std::optional<Polygon> CreatePolygon(std::vector<Math::Vec2f> points);

	std::ostream& operator<<(std::ostream& os, const Polygon& polygon);
	bool operator==(const Polygon& polygon1, const Polygon& polygon2);
	bool operator!=(const Polygon& polygon1, const Polygon& polygon2);

}