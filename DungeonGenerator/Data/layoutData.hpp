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

	public:
		LayoutData(const Geometry::Polygon& polygon) : polygon(polygon)
		{
			for (Math::Vec2f p : polygon.getPoints())
				points.push_back(Math::Vec3f(p[0], p[1], 0.0f));

			for (int idx = 1; idx < points.size() - 1; ++idx)
			{
				triangles.push_back(Math::Vec3i(idx + 1, idx, 0));
				counterTriangles.push_back(Math::Vec3i(0, idx, idx + 1));
			}
		}


		std::vector<Math::Vec3i> getTrianglesClockWise() const
		{
			/*std::vector<Math::Vec3i> triangles;

			triangles.push_back(Math::Vec3i{ 0, 1, 2 });
			triangles.push_back(Math::Vec3i{ 0, 2, 3 });*/

			return triangles;
		}

		std::vector<Math::Vec3i> getTrianglesCounterClockwise() const
		{
			return counterTriangles;
		}

		std::vector<Math::Vec3f> getPoints() const
		{
			/*std::vector<Math::Vec3f> points;

			points.push_back(Math::Vec3f{   0.0f,   0.0f, 0.0f });
			points.push_back(Math::Vec3f{   0.0f, 100.0f, 0.0f });
			points.push_back(Math::Vec3f{ 100.0f, 100.0f, 0.0f });
			points.push_back(Math::Vec3f{ 100.0f,   0.0f, 0.0f });

			return points;*/

			return points;
		}
	};

}