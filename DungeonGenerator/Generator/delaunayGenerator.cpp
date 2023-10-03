#include "delaunayGenerator.hpp"
#include "delaunay.hpp"
#include "equationSystem.hpp"
#include "geometry.hpp"

namespace Generator
{

	void DelaunayBasedGeneratorAlgorithm::generatePoints()
	{
		for (int idx = 0; idx < pointCount; ++idx)
		{
			Math::Vec2f newPoint;

			// TODO generate points

			points.push_back(newPoint);
		}
	}

	std::vector<Geometry::Polygon> DelaunayBasedGeneratorAlgorithm::createPolygons(const std::vector<Geometry::Delaunay::Triangle>& triangles) const
	{
		//TODO
		return std::vector<Geometry::Polygon>();
	}

	Math::Vec2f DelaunayBasedGeneratorAlgorithm::calcOutterCircleCenter(const Geometry::Delaunay::Triangle& triangle) const
	{
		Math::Vec2f A = points[0];
		Math::Vec2f B = points[1];
		Math::Vec2f C = points[2];

		return Geometry::calcTriangleOutterCircleCenter({ A, B, C });
	}

	DelaunayBasedGeneratorAlgorithm::DelaunayBasedGeneratorAlgorithm(const DungeonGeneratorSettings& settings)
		: pointCount(settings.getRoomCount())
	{

	}

	void DelaunayBasedGeneratorAlgorithm::Generate(Data::DungeonData& dungeonData)
	{
		Geometry::Delaunay::DelaunayTriangulator triangulator(points);

		std::vector<Geometry::Delaunay::Triangle> triangles = triangulator.Triangulate(Geometry::Delaunay::ClockWise);


		for (Geometry::Polygon poly : createPolygons(triangles))
		{
			dungeonData.floors.push_back(Data::LayoutData(poly));
		}

		for (const Data::LayoutData& poly : dungeonData.floors)
		{
			std::vector<Math::Vec3f> points = poly.getPoints();
			for (int idx = 0; idx < points.size() - 1; ++idx)
			{
				dungeonData.walls.push_back(Data::WallData(points[idx], points[idx + 1]));
			}
			dungeonData.walls.push_back(Data::WallData(points[points.size() - 1], points[0]));
		}
	}

}
