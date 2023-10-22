#pragma once

#include "polygon.hpp"
#include "delaunayBase.hpp"
#include <set>


namespace Geometry::Delaunay
{

	class PolygonTriangulator
	{
	private:
		Polygon						polygon;
		std::vector<Math::Vec2f>	vertices;
		std::set<int>				holeIds;

		void removeHoles(DelaunayTriangulation& triangulation) const;
		void getVertices();
	public:
		PolygonTriangulator(const Polygon& polygon);

		DelaunayTriangulation Triangulate(TriangleDirection direction = CounterClockWise);
	};

}