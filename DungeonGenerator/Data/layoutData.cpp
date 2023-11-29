#include "layoutData.hpp"

#include "polygonTriangulator.hpp"

namespace Data
{
	LayoutData::LayoutData(const Geometry::Polygon& polygon) : polygon(polygon)
	{
		triangulate();
	}

	Geometry::Polygon LayoutData::getPolygon() const
	{
		return polygon;
	}

	void LayoutData::setPolygon(const Geometry::Polygon& polygon)
	{
		this->polygon = polygon;
		triangulate();
	}

	void LayoutData::triangulate()
	{
		Geometry::Delaunay::PolygonTriangulator triangulator(polygon);
		Geometry::Delaunay::DelaunayTriangulation triangulation = triangulator.Triangulate(Geometry::Delaunay::ClockWise);

		points.clear();

		for (Math::Vec2f p : triangulation.Vertices)
			points.push_back(Math::Vec3f(p[0], p[1], 0.0f));

		triangles.clear();
		counterTriangles.clear();

		for (const auto& triangle : triangulation.Triangles)
		{
			triangles.push_back(Math::Vec3i(triangle.P0.index, triangle.P1.index, triangle.P2.index));
			counterTriangles.push_back(Math::Vec3i(triangle.P2.index, triangle.P1.index, triangle.P0.index));
		}
	}

	std::vector<Math::Vec3i> LayoutData::getTrianglesClockWise() const
	{
		return triangles;
	}

	std::vector<Math::Vec3i> LayoutData::getTrianglesCounterClockwise() const
	{
		return counterTriangles;
	}

	std::vector<Math::Vec3f> LayoutData::getPoints() const
	{
		return points;
	}

}