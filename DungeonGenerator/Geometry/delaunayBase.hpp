#pragma once
#include <array>
#include <vector>

#include "vector.hpp"
#include "graph.hpp"


namespace Geometry::Delaunay
{

	enum TriangleDirection { ClockWise, CounterClockWise, NotMatters };

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

		bool						hasPoint(const PointIndex& P) const;
		bool						hasEdge(const Edge& edge) const;
		std::array<Edge, 3>			getEdges() const;
		std::array<PointIndex, 3>	getPoints() const;

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
	
}

namespace std
{
	template <>
	struct hash<Geometry::Delaunay::DelaunayTriangulation>
	{
		size_t operator()(const Geometry::Delaunay::DelaunayTriangulation& record) const noexcept
		{
			return hash<int>()(record.Triangles.size());
		}
	};
}