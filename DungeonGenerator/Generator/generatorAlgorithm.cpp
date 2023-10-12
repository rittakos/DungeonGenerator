#include "generatorAlgorithm.hpp"
#include <math.h>
#include "log.h"

namespace Generator
{
	bool VoronoiBasedGeneratorAlgorithm::equals(const Math::Vec2f& P1, const Math::Vec2f& P2) const
	{
		return fabs(P1[0] - P2[0]) < epsilon && fabs(P1[1] - P2[1]) < epsilon;
	}


	bool VoronoiBasedGeneratorAlgorithm::contains(const std::vector<Math::Vec2f>& vector, const Math::Vec2f& P) const
	{
		for (const auto& p : vector)
		{
			if (equals(p, P))
				return true;
		}
		return false;
	}


	std::vector<Geometry::Line> VoronoiBasedGeneratorAlgorithm::getBisectors(const Math::Vec2i& cell, const Math::Vec2f& P) const
	{
		std::vector<Geometry::Line> lines;

		for (int dx = -1; dx <= 1; ++dx)
		{
			for (int dy = -1; dy <= 1; ++dy)
			{
				if (dx == 0 && dy == 0)
					continue;

				int idx = cell[0] + dx + (cell[1] + dy) * width;
				Math::Vec2f P1 = Math::Vec2f(centers[idx][0], centers[idx][1]);

				lines.push_back(Geometry::getBisector(P, P1));
			}
		}

		return lines;
	}

	std::vector<Math::Vec2f> VoronoiBasedGeneratorAlgorithm::getIntersectionPoints(const std::vector<Geometry::Line>& lines) const
	{
		std::vector<Math::Vec2f> points;

		for (int idx = 0; idx < lines.size() - 1; ++idx)
		{
			for (int idy = idx + 1; idy < lines.size(); ++idy)
			{
				std::optional<Math::Vec2f> Q = Geometry::getIntersectionPoint(lines[idx], lines[idy]);
				if (Q.has_value() && !contains(points, Q.value()))
					points.push_back(Q.value());
			}
		}

		return points;
	}

	std::vector<Math::Vec2f> VoronoiBasedGeneratorAlgorithm::getCornersFromIntersectionPoints(
											const std::vector<Math::Vec2f>& intersectionPoints, 
											const std::vector<Geometry::Line>& lines, 
											const Math::Vec2f& P, 
											const Math::Vec2i& coord) const
	{
		std::vector<Math::Vec2f> corners;

		for (const Math::Vec2f& p : intersectionPoints)
		{
			float d = (P - p).length();
			if (d > maxRadius)
				continue;
			bool add = true;

			for (int dx = -1; dx <= 1; ++dx)
			{
				for (int dy = -1; dy <= 1; ++dy)
				{
					if (dx == 0 && dy == 0)
						continue;

					int idx1 = coord[0] + dx + (coord[1] + dy) * width;
					Math::Vec2f P1 = Math::Vec2f(centers[idx1][0], centers[idx1][1]);

					if ((P1 - p).length() < d - maxRadius * 0.01f)
					{
						add = false;
						break;
					}
				}
			}

			if (add /*&& std::find(corners.begin(), corners.end(), p) == corners.end()*/)
				corners.push_back(p);
		}

		return corners;
	}

	Geometry::Polygon VoronoiBasedGeneratorAlgorithm::getPolyFromCorners(const std::vector<Math::Vec2f>& corners, const std::vector<Geometry::Line>& bisectors, const Math::Vec2f& P) const
	{
		Geometry::Polygon poly;

		if (corners.size() < 3)
			return poly;

		std::vector<Geometry::Line> chosenLines;

		Math::Vec2f previusPoint = corners[0];
		poly.addPoint(previusPoint);

		while (poly.getPoints().size() != corners.size())
		{
			for (int idx = 1; idx < corners.size(); ++idx)
			{
				for (Geometry::Line l : bisectors)
				{
					if (!l.containsPoint(previusPoint) ||
						std::find(chosenLines.begin(), chosenLines.end(), l) != chosenLines.end())
						continue;

					chosenLines.push_back(l);

					for (Math::Vec2f c : corners)
					{
						if (previusPoint == c)
							continue;
						if (!l.containsPoint(c))
							continue;
						if (poly.containsPoint(c))
							continue;
						poly.addPoint(c);
						previusPoint = c;
					}
				}
			}
		}

		if (!poly.exists())
		{
			Geometry::Polygon newPoly;
			newPoly.addPoint(poly.getPoints()[0]);
			for (int idx = poly.getPoints().size() - 1; idx > 0; --idx)
				newPoly.addPoint(poly.getPoints()[idx]);
			poly = newPoly;
		}

		return poly;
	}


	void VoronoiBasedGeneratorAlgorithm::generateCenters(const Math::Vec2f& cellSize, const Math::Vec3f& leftUpCorner)
	{
		/*centers.push_back(Math::Vec3f(75.0f, 50.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 50.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(250.0f, 50.0f, leftUpCorner[2]));

		centers.push_back(Math::Vec3f(50.0f, 150.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 150.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(250.0f, 150.0f, leftUpCorner[2]));

		centers.push_back(Math::Vec3f(50.0f, 250.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 250.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(250.0f, 250.0f, leftUpCorner[2]));*/


		/*centers.push_back(Math::Vec3f(75.0f, 50.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 50.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(220.0f, 50.0f, leftUpCorner[2]));

		centers.push_back(Math::Vec3f(75.0f, 150.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 150.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(225.0f, 150.0f, leftUpCorner[2]));

		centers.push_back(Math::Vec3f(75.0f, 250.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 250.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(225.0f, 250.0f, leftUpCorner[2]));*/

		/*centers.push_back(Math::Vec3f(50.0f, 50.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(50.0f, 150.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(50.0f, 250.0f, leftUpCorner[2]));

		centers.push_back(Math::Vec3f(150.0f, 50.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 150.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 250.0f, leftUpCorner[2]));

		centers.push_back(Math::Vec3f(250.0f, 50.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(250.0f, 150.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(250.0f, 250.0f, leftUpCorner[2]));*/

		/*centers.push_back(Math::Vec3f(75.0f, 50.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 50.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(220.0f, 50.0f, leftUpCorner[2]));

		centers.push_back(Math::Vec3f(75.0f, 150.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 150.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(225.0f, 150.0f, leftUpCorner[2]));

		centers.push_back(Math::Vec3f(75.0f, 250.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(150.0f, 250.0f, leftUpCorner[2]));
		centers.push_back(Math::Vec3f(225.0f, 250.0f, leftUpCorner[2]));*/

		for (int row = 0; row < height; ++row)
		{
			for (int col = 0; col < width; ++col)
			{
				float minX = leftUpCorner[0] + col * cellSize[0];
				float minY = leftUpCorner[1] + row * cellSize[1];

				float x = Random::GetFloat(minX + (cellSize[0] / 4.0f), minX + (3.0f * cellSize[0] / 4.0f));
				//float x = minX + cellSize[0] / 2.0;
				float y = Random::GetFloat(minY + (cellSize[1] / 4.0f), minY + (3.0f * cellSize[1] / 4.0f));
				//float y = minY + cellSize[1] / 2.0;

				centers.push_back(Math::Vec3f(x, y, leftUpCorner[2]));
			}
		}
	}


	std::vector<Geometry::Polygon> VoronoiBasedGeneratorAlgorithm::generatePolygons()
	{
		std::vector<Geometry::Polygon> polygons;

		for (int row = 1; row < height - 1; ++row)
		{
			for (int col = 1; col < width - 1; ++col)
			{
				int idx = col + row * width;
				Math::Vec2f P = Math::Vec2f(centers[idx][0], centers[idx][1]);

				std::vector<Geometry::Line> bisectors			= getBisectors(Math::Vec2i(col, row), P);
				//Log::info("Bisectors");
				std::vector<Math::Vec2f>	intersectionPoints	= getIntersectionPoints (bisectors);
				//Log::info("Intersection Points");
				std::vector<Math::Vec2f>	corners				= getCornersFromIntersectionPoints(intersectionPoints, bisectors, P, Math::Vec2i(col, row));
				//Log::info("Corners");

				std::optional<Geometry::Polygon> poly = getAllPolygons (corners);
				//Log::info("Poly");

				if (poly.has_value() && poly->exists())
				{
					polygons.push_back(*poly);
					//std::cout << poly << std::endl;
				}
				else
					Log::error("Non existing Polygon!");
			}
		}

		return polygons;
	}
}