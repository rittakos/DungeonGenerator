#include "delaunayGenerator.hpp"
#include "delaunay.hpp"
#include "equationSystem.hpp"
#include "geometry.hpp"

namespace Generator
{

	void DelaunayBasedGeneratorAlgorithm::generatePoints()
	{
		//for (int idx = 0; idx < pointCount; ++idx)
		{
			//Math::Vec2f newPoint;

			for (int col = 0; col < 3; col++)
			{
				for (int row = 0; row < 3; row++)
				{
					points.push_back(Math::Vec2f{row * 100.0f, col * 100.0f});
				}
			}

			//points.push_back(newPoint);
		}
	}

	std::vector<Geometry::Polygon> DelaunayBasedGeneratorAlgorithm::createPolygons(const Geometry::Delaunay::DelaunayTriangulation& triangulation) const
	{
		//std::map<int, std::vector<Geometry::Delaunay::Triangle>> point;
		std::vector<std::vector<Geometry::Delaunay::Triangle>> points(triangulation.Vertices.size());
		for (const auto& triangle : triangulation.Triangles)
		{
			points[triangle.P0.index].push_back(triangle);
			points[triangle.P1.index].push_back(triangle);
			points[triangle.P2.index].push_back(triangle);
		}

		std::vector<int> relevantPoints;
		for (int idx = 0; idx < points.size(); ++idx)
		{
			Math::Angle sumAngle = getSumAngleAroundPoint(idx, points[idx]);
			if (sumAngle == 360.0_deg)
				relevantPoints.push_back(idx);
		}

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

	Math::Angle DelaunayBasedGeneratorAlgorithm::getSumAngleAroundPoint(int pointIdx, const std::vector<Geometry::Delaunay::Triangle>& trainglesAround) const
	{
		Math::Angle angle = 0.0_deg;
		for (const auto& triangle : trainglesAround)
			angle += getAngleOfTriangle(triangle, pointIdx);
		return angle;
	}

	Math::Angle DelaunayBasedGeneratorAlgorithm::getAngleOfTriangle(const Geometry::Delaunay::Triangle& triangle, int pointIdx) const
	{
		Math::Angle angle;

		int center;
		int P0;
		int P1;
		if (triangle.P0 == pointIdx)
		{
			center = triangle.P0.index;
			P0 = triangle.P2.index;
			P1 = triangle.P1.index;
		}
		else if (triangle.P1 == pointIdx)
		{
			center = triangle.P1.index;
			P0 = triangle.P0.index;
			P1 = triangle.P2.index;
		}
		else if (triangle.P2 == pointIdx)
		{
			center = triangle.P2.index;
			P0 = triangle.P0.index;
			P1 = triangle.P1.index;
		}
		

		angle = Math::getAngle(triangulation.Vertices[P0], triangulation.Vertices[center], triangulation.Vertices[P1]);
		
		if (angle > 180.0_deg)
			angle = 360.0_deg - angle;

		return angle;
	}

	DelaunayBasedGeneratorAlgorithm::DelaunayBasedGeneratorAlgorithm(const DungeonGeneratorSettings& settings)
		: pointCount(settings.getRoomCount())
	{

	}

	void DelaunayBasedGeneratorAlgorithm::Generate(Data::DungeonData& dungeonData)
	{
		generatePoints();
		Geometry::Delaunay::DelaunayTriangulator triangulator(points);

		triangulation = triangulator.Triangulate(Geometry::Delaunay::ClockWise);


		for (Geometry::Polygon poly : createPolygons(triangulation))
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
