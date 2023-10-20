#pragma once

#include "polygon.hpp"
#include "delaunay.hpp"
#include "delaunayBase.hpp"


namespace Geometry::Delaunay
{

	class PolygonTriangulator
	{
	public:
		PolygonTriangulator(const Polygon& polygon);

		DelaunayTriangulation Triangulate(TriangleDirection direction = CounterClockWise);
	};

}