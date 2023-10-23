#include <math.h>
#include "voronoiGenerator.hpp"
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

	bool VoronoiBasedGeneratorAlgorithm::isConvex(std::vector<Math::Vec2f>& polygon) const
	{
		int n = polygon.size();
		int orientation = 0;
		for (int i = 0; i < n; i++) {
			int dx1 = polygon[(i + 1) % n][0] - polygon[i][0];
			int dy1 = polygon[(i + 1) % n][1] - polygon[i][0];
			int dx2 = polygon[(i + 2) % n][0] - polygon[(i + 1) % n][0];
			int dy2 = polygon[(i + 2) % n][1] - polygon[(i + 1) % n][1];
			int crossProduct = dx1 * dy2 - dy1 * dx2;
			if (i == 0) {
				orientation = crossProduct;
			}
			else {
				if (crossProduct * orientation < 0) {
					return false;
				}
			}
		}
		return true;
	}

	bool VoronoiBasedGeneratorAlgorithm::isValidTriangle(Math::Vec2f a, Math::Vec2f b, Math::Vec2f c) const
	{
		double side1 = distance(a, b);
		double side2 = distance(b, c);
		double side3 = distance(c, a);
		if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1) {
			return true;
		}
		return false;
	}

	void VoronoiBasedGeneratorAlgorithm::getPolygons(std::vector<Math::Vec2f>& points) const
	{
		int n = points.size();
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (int k = j + 1; k < n; k++) {
					std::vector<Math::Vec2f> polygon;
					polygon.push_back(points[i]);
					polygon.push_back(points[j]);
					polygon.push_back(points[k]);
					if (isValidTriangle(points[i], points[j], points[k])) {
						for (int l = 0; l < n; l++) {
							if (l != i && l != j && l != k) {
								polygon.push_back(points[l]);
								if (polygon.size() >= 5 && isConvex(polygon)) {
									std::cout << "Polygon: ";
									for (int m = 0; m < polygon.size(); m++) {
										std::cout << "(" << polygon[m][0] << ", " << polygon[m][1] << ")";
										if (m != polygon.size() - 1) {
											std::cout << ", ";
										}
									}
									std::cout << std::endl;
								}
								polygon.pop_back();
							}
						}
					}
				}
			}
		}
	}

	std::optional<Geometry::Polygon> VoronoiBasedGeneratorAlgorithm::getAllPolygons(std::vector<Math::Vec2f>& points) const
	{
		int n = points.size();
		int* arr = new int[points.size()]();
		for (int idx = 0; idx < n; ++idx)
			arr[idx] = idx;

		std::optional<Geometry::Polygon> polygon;
		bool multiplePolygonFound = false;

		// Get all permutations of the array
		do {
			Geometry::Polygon poly;
			for (int i = 0; i < n; i++)
			{
				poly.addPoint(points[arr[i]]);
			}
			/*if (poly.getPoints()[0] == points[0] && poly.getPoints()[1] == points[2] &&
				poly.getPoints()[2] == points[3] && poly.getPoints()[3] == points[5] &&
				poly.getPoints()[4] == points[4] && poly.getPoints()[5] == points[1])*/
				/*if (poly.getPoints()[0] == points[0] && poly.getPoints()[1] == points[4] &&
					poly.getPoints()[2] == points[1] && poly.getPoints()[3] == points[5] &&
					poly.getPoints()[4] == points[2] && poly.getPoints()[5] == points[3])
					std::cout << "xxx" << std::endl;*/
					/*if (arr[0] == 0 && arr[1] == 1 &&
						arr[2] == 3 && arr[3] == 4 &&
						arr[4] == 2)
						std::cout << "xxx" << std::endl;*/
						/*if (arr[0] == 0 && arr[1] == 2 &&
							arr[2] == 5 && arr[3] == 4 &&
							arr[4] == 3 && arr[5] == 1)
							std::cout << "xxx" << std::endl;*/
			if (poly.exists() && poly.getPoints().size() == n)
			{
				if (polygon.has_value() && poly == polygon.value())
					continue;
				//std::cout << poly << std::endl;
				if (polygon.has_value())
				{
					//std::cout << poly << std::endl;
					multiplePolygonFound = true;
					break;
				}
				else
					polygon = poly;
			}
		} while (std::next_permutation(arr, arr + n));

		if (multiplePolygonFound)
		{
			//Log::warn("Multiple Polygon Found!");
			return {};
		}

		/*if (!polygon.has_value())
			Log::error("No polygon found!");*/

		delete[] arr;

		return polygon;
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

				std::vector<Geometry::Line> bisectors = getBisectors(Math::Vec2i(col, row), P);
				//Log::info("Bisectors");
				std::vector<Math::Vec2f>	intersectionPoints = getIntersectionPoints(bisectors);
				//Log::info("Intersection Points");
				std::vector<Math::Vec2f>	corners = getCornersFromIntersectionPoints(intersectionPoints, bisectors, P, Math::Vec2i(col, row));
				//Log::info("Corners");

				std::optional<Geometry::Polygon> poly = getAllPolygons(corners);
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


	void VoronoiBasedGeneratorAlgorithm::Generate(Data::DungeonData& dungeonData)
	{
		const Math::Vec2i roomCount(3, 3);
		const Math::Vec2f roomSize(1000.0f, 1000.0f);
		const Math::Vec3f origo(0.0f, 0.0f, 0.0f);

		//std::vector<Math::Vec2f> points;
		//points.push_back(Math::Vec2f{0.0f, 0.0f});
		//points.push_back(Math::Vec2f{0.0f, 1.0f});
		//points.push_back(Math::Vec2f{1.0f, 1.0f});
		//points.push_back(Math::Vec2f{1.0f, 0.0f});
		//points.push_back(Math::Vec2f{2.0f, 0.5f});
		////getPolygons(points);

		//getAllPolygons(points);

		maxRadius = roomSize.length();

		width = roomCount[0] + 2;
		height = roomCount[1] + 2;

		generateCenters(roomSize, origo);
		//Log::info("Centers Generated!");

		for (Geometry::Polygon poly : generatePolygons())
		{
			Data::RoomData room(poly);
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

		//Log::info("Dungeon Generated by Voronoi Based Algorithm");
	}
}