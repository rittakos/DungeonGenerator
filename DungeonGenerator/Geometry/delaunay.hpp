#pragma once
#include <vector>
#include <array>
#include <vector.hpp>
#include <graph.hpp>
#include <optional>

#include "delaunayBase.hpp"


namespace Geometry
{
	namespace Delaunay
	{
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
			DelaunayTriangulator(const std::vector<Math::Vec2f>& vertices);

			DelaunayTriangulation Triangulate(TriangleDirection direction = CounterClockWise); // gives the indexes of the points in the original vector
		};

	}
}
