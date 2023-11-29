#pragma once

#include "polygon.hpp"

namespace Data
{

	class LayoutData
	{
	private:
		Geometry::Polygon polygon;

		std::vector<Math::Vec3f> points;
		std::vector<Math::Vec3i> triangles;
		std::vector<Math::Vec3i> counterTriangles;

		void triangulate();

	public:
		LayoutData(const Geometry::Polygon& polygon);

		Geometry::Polygon getPolygon() const;
		void setPolygon(const Geometry::Polygon& polygon);

		std::vector<Math::Vec3i> getTrianglesClockWise() const;
		std::vector<Math::Vec3i> getTrianglesCounterClockwise() const;
		std::vector<Math::Vec3f> getPoints() const;
	};

}