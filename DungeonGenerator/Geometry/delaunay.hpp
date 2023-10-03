#pragma once
#include <vector>
#include <array>
#include <vector.hpp>
#include <graph.hpp>
#include <optional>


namespace Geometry
{
	namespace Delaunay
	{

		enum TriangleDirection {ClockWise, CounterClockWise, NotMatters};

		// For the more precise calcualtions the algorithm is refer the points by the index of the given array. 

		class PointIndex
		{
		public:
			bool superTriangle;
			int index;

			PointIndex(int index = 0) : index(index), superTriangle(false) {}
			PointIndex(int index, bool superTriangle) : index(index), superTriangle(superTriangle) {}

			PointIndex& operator=(const PointIndex& other);
			bool		operator==(const PointIndex& other) const;
		};

		class Edge
		{
		public:
			PointIndex P0;
			PointIndex P1;

			Edge& operator=(const Edge& other);
		};

		class Triangle
		{
		public:
			PointIndex P0;
			PointIndex P1;
			PointIndex P2;

			Triangle() = default;

			Triangle(const PointIndex& p0, const PointIndex& p1, const PointIndex& p2);

			bool				hasPoint(const PointIndex& P) const;
			bool				hasEdge(const Edge& edge) const;
			std::array<Edge, 3> getEdges() const;

			void rotate();

			bool operator==(const Triangle& other) const;

		};


		struct DelaunayTriangulation
		{
			std::vector<Math::Vec2f>	Vertices;
			std::vector<Triangle>		Triangles;
			Math::Graph<Triangle>		Neighbours;

			bool operator ==(const DelaunayTriangulation& other) const
			{
				return Vertices == other.Vertices && Triangles == other.Triangles && Neighbours == other.Neighbours;
			}
		};
		

		class DelaunayTriangulator
		{
		private:
			std::vector<Math::Vec2f> vertices;
			std::array<Math::Vec2f, 3> superTriangleVertices;

		private:
			std::vector<Triangle> triangulate();

			bool		isPointInTrianglesCircle(Triangle triangle, const PointIndex& P) const;
			Triangle	createSuperTriangle();
			Math::Vec2f getValueOfPoint(const PointIndex& pointIdx) const;

			void transformAllTriangles(std::vector<Triangle>& triangles, TriangleDirection direction) const;

			bool isClockWise(const Triangle& triangle) const;

			std::optional<Edge> hasCommonEdge(const Triangle& triangle1, const Triangle& triangle2) const;

			Math::Graph<Triangle> getNeighbourhoodGraph(const std::vector<Triangle>& triangulation) const;
		public:
			DelaunayTriangulator(std::vector<Math::Vec2f> vertices);

			DelaunayTriangulation Triangulate(TriangleDirection direction = CounterClockWise); // gives the indexes of the points in the original vector
		};

	}

}

namespace std
{
	template <>
	struct hash<Geometry::Delaunay::DelaunayTriangulation> 
	{
		size_t operator()(const Geometry::Delaunay::DelaunayTriangulation& record) const
		{
			return hash<int>()(record.Triangles.size());
		}
	};
}