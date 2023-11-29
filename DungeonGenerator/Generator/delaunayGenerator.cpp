#include "delaunayGenerator.hpp"
#include "delaunay.hpp"
#include "geometry.hpp"

namespace Generator
{

	void DelaunayBasedGeneratorAlgorithm::generatePoints()
	{
		// MUST kirakni valahova
		//for (int idx = 0; idx < pointCount; ++idx)
		{
			//Math::Vec2f newPoint;

			float i = 0.0f;

			for (int col = 0; col < 10; col++)
			{
				for (int row = 0; row < 10; row++)
				{
					points.push_back(Math::Vec2f{row * 100.0f, col * 100.0f + i});
					i += 20.0f;
				}
			}

			//points.push_back(newPoint);
		}
	}

	std::vector<Geometry::Polygon> DelaunayBasedGeneratorAlgorithm::createPolygons(const Geometry::Delaunay::DelaunayTriangulation& triangulation) const
	{
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

		std::vector<std::vector<int>> polygonsWithIndices; // TODO mi van it???? nope
		std::vector<Geometry::Polygon> polygons;

		for (int i = 0; i < relevantPoints.size(); ++i)
		{
			int p = relevantPoints[i];
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

		Math::Graph<int, Geometry::Edge> maze;

		for (Geometry::Polygon poly : createPolygons(triangulation))
		{
			Data::RoomData room (poly);
			dungeonData.addRoom(room);
			maze.addNode(room.getId());
		}

		const int roomCount = dungeonData.getRooms().size();
		
		for (int roomIdx1 = 0; roomIdx1 < roomCount - 1; ++roomIdx1)
		{
			Data::RoomData room1 = dungeonData.getRooms()[roomIdx1];
			for (int roomIdx2 = roomIdx1 + 1; roomIdx2 < roomCount; ++roomIdx2)
			{
				Data::RoomData room2 = dungeonData.getRooms()[roomIdx2];
				std::optional<Geometry::Edge> commonEdge = Geometry::getCommonEdge(room1.getFloor().getPolygon(), room2.getFloor().getPolygon());
				if (commonEdge.has_value())
				{
					maze.addEdge(room1.getId(), room2.getId(), commonEdge.value());
					maze.addEdge(room2.getId(), room1.getId(), commonEdge.value());
				}
			}
		}

		dungeonData.getMaze().setGraph(maze);
	}

}
