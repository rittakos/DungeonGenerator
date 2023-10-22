#pragma once

#include "polygon.hpp"
#include "polygonTriangulator.hpp"

namespace Data
{

	class LayoutData
	{
	private:
		Geometry::Polygon polygon;

		std::vector<Math::Vec3f> points;
		std::vector<Math::Vec3i> triangles;
		std::vector<Math::Vec3i> counterTriangles;

	public:
		LayoutData(const Geometry::Polygon& polygon) : polygon(polygon)
		{
			/*for (Math::Vec2f p : polygon.getPoints())
				points.push_back(Math::Vec3f(p[0], p[1], 0.0f));*/

			//Geometry::Delaunay::DelaunayTriangulator triangulator(polygon.getPoints());
			//Geometry::Delaunay::DelaunayTriangulation triangulation = triangulator.Triangulate(Geometry::Delaunay::ClockWise);
			
			Geometry::Delaunay::PolygonTriangulator triangulator(polygon);
			Geometry::Delaunay::DelaunayTriangulation triangulation = triangulator.Triangulate(Geometry::Delaunay::ClockWise);
				
			for (Math::Vec2f p : triangulation.Vertices)
				points.push_back(Math::Vec3f(p[0], p[1], 0.0f));

			for (const auto& triangle : triangulation.Triangles)
			{
				triangles.push_back(Math::Vec3i(triangle.P0.index, triangle.P1.index, triangle.P2.index));
				counterTriangles.push_back(Math::Vec3i(triangle.P2.index, triangle.P1.index, triangle.P0.index));
			}

			/*for (int idx = 1; idx < points.size() - 1; ++idx)
			{
				triangles.push_back(Math::Vec3i(idx + 1, idx, 0));
				counterTriangles.push_back(Math::Vec3i(0, idx, idx + 1));
			}*/
		}


		std::vector<Math::Vec3i> getTrianglesClockWise() const
		{
			return triangles;
		}

		std::vector<Math::Vec3i> getTrianglesCounterClockwise() const
		{
			return counterTriangles;
		}

		std::vector<Math::Vec3f> getPoints() const
		{
			return points;
		}
	};

}