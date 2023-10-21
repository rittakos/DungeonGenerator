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

			float i = 0.0f;

			for (int col = 0; col < 3; col++)
			{
				for (int row = 0; row < 3; row++)
				{
					points.push_back(Math::Vec2f{row * 100.0f, col * 100.0f + i});
					i += 10.0f;
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

		std::vector<std::vector<int>> polygonsWithIndices; //nope
		std::vector<Geometry::Polygon> polygons;

		for (int i = 0; i < relevantPoints.size(); ++i)
		{
			int p = relevantPoints[i];
			//std::vector<Geometry::Delaunay::Triangle> trianglesInOrder;
			std::vector<int> trianglesInOrder;
			trianglesInOrder.push_back(0);
			while (trianglesInOrder.size() != points[p].size())
			{
				for (int idx = 1; idx < points[p].size(); ++idx)
				{
					if (std::find(trianglesInOrder.begin(), trianglesInOrder.end(), idx) != std::end(trianglesInOrder))
						continue;
					if (triangulation.Neighbours.containsEdge(points[p][idx], points[p][trianglesInOrder.back()]))
						trianglesInOrder.push_back(idx);
				}
			}

			Geometry::Polygon newPolygon;

			for (int triangleId : trianglesInOrder)
			{
				newPolygon.addPoint(calcOutterCircleCenter(points[p][triangleId]));
			}

			polygons.push_back(newPolygon);
		}

		//TODO
		return polygons;
	}

	Math::Vec2f DelaunayBasedGeneratorAlgorithm::calcOutterCircleCenter(const Geometry::Delaunay::Triangle& triangle) const
	{
		Math::Vec2f A = points[triangle.P0.index];
		Math::Vec2f B = points[triangle.P1.index];
		Math::Vec2f C = points[triangle.P2.index];

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
			Geometry::Polygon hole;

			hole.addPoint(Math::Vec2f(90.0f, 90.0f));
			hole.addPoint(Math::Vec2f(90.0f, 120.0f));
			hole.addPoint(Math::Vec2f(120.0f, 90.0f));
			hole.addPoint(Math::Vec2f(120.0f, 120.0f));

			bool succes = poly.addHole(hole);
			if (!succes)
				std::cout << "cant add hole";

			Data::RoomData room (poly);
			dungeonData.addRoom(room);
			//dungeonData.floors.push_back(Data::LayoutData(poly));
		}

		/*for (const Data::LayoutData& poly : dungeonData.floors)
		{
			std::vector<Math::Vec3f> points = poly.getPoints();
			for (int idx = 0; idx < points.size() - 1; ++idx)
			{
				dungeonData.walls.push_back(Data::WallData(points[idx], points[idx + 1]));
			}
			dungeonData.walls.push_back(Data::WallData(points[points.size() - 1], points[0]));
		}*/
	}

}
