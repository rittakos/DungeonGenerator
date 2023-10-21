#include "polygonTriangulator.hpp"



namespace Geometry::Delaunay
{


	PolygonTriangulator::PolygonTriangulator(const Polygon& polygon) : polygon (polygon)
	{

	}

	void PolygonTriangulator::removeHoles(DelaunayTriangulation& triangulation) const
	{
		if (polygon.getHoles().empty())
			return;

		std::vector<Triangle> neededTriangles;

		for (const Triangle& triangle : triangulation.Triangles)
		{
			if (holeIds.contains(triangle.P0.index) &&
				holeIds.contains(triangle.P1.index) &&
				holeIds.contains(triangle.P2.index))
			{
				continue;
			}

			neededTriangles.push_back(triangle);
		}

		triangulation.Triangles = neededTriangles;

	}


	void PolygonTriangulator::getVertices()
	{
		std::vector<Math::Vec2f> outline = polygon.getPoints();

		vertices.insert(std::end(vertices), std::begin(outline), std::end(outline));

		int lastId = vertices.size() - 1;

		for (const Polygon& hole : polygon.getHoles())
		{
			for (const Math::Vec2f& p : hole.getPoints())
			{
				++lastId;
				vertices.push_back(p);
				holeIds.insert(lastId);
			}
		}
	}


	DelaunayTriangulation PolygonTriangulator::Triangulate(TriangleDirection direction)
	{
		getVertices();

		DelaunayTriangulator triangulator(vertices);
		DelaunayTriangulation triangulation = triangulator.Triangulate(direction);

		removeHoles(triangulation);

		return triangulation;
	}
}