#pragma once
#include <algorithm>
#include "dungeonData.hpp"

namespace Generator
{

	class GeneratorAlgorithm
	{
	public:
		virtual void Generate(Data::DungeonData& dungeonData) = 0;
		//virtual void operator()() = 0;
	};

	class VoronoiBasedGeneratorAlgorithm : public GeneratorAlgorithm
	{
	private:
		int width;			// count of the horisontal cells
		int height;			//count of the horisontal cells

		float maxRadius;	// if the distance of a point is greater than this, 
							// than the point belong to an other point

		std::vector<Math::Vec3f> centers;

		const float epsilon = 0.0001f;

	private:
		bool equals(const Math::Vec2f& P1, const Math::Vec2f& P2) const;
		bool contains(const std::vector<Math::Vec2f>& vector, const Math::Vec2f& P) const;


	private:
		std::vector<Geometry::Line> getBisectors(const Math::Vec2i& coord, const Math::Vec2f& P) const;
		std::vector<Math::Vec2f> getIntersectionPoints(const std::vector<Geometry::Line>& lines) const;
		std::vector<Math::Vec2f> getCornersFromIntersectionPoints(	const std::vector<Math::Vec2f>& intersectionPoints, 
																	const std::vector<Geometry::Line>& lines, 
																	const Math::Vec2f& P,
																	const Math::Vec2i& coord) const;
		Geometry::Polygon getPolyFromCorners(	const std::vector<Math::Vec2f>& corners, 
												const std::vector<Geometry::Line>&lines, 
												const Math::Vec2f& P) const;


		bool isConvex(std::vector<Math::Vec2f>& polygon) {
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

		bool isValidTriangle(Math::Vec2f a, Math::Vec2f b, Math::Vec2f c) {
			double side1 = distance(a, b);
			double side2 = distance(b, c);
			double side3 = distance(c, a);
			if (side1 + side2 > side3 && side1 + side3 > side2 && side2 + side3 > side1) {
				return true;
			}
			return false;
		}


		void getPolygons(std::vector<Math::Vec2f>& points) {
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

		std::optional<Geometry::Polygon> getAllPolygons(std::vector<Math::Vec2f>& points)
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

		void generateCenters(const Math::Vec2f& cellSize, const Math::Vec3f& leftUpCorner);

		std::vector<Geometry::Polygon> generatePolygons();

	public:
		virtual void Generate(Data::DungeonData& dungeonData) override
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

			//Log::info("Dungeon Generated by Voronoi Based Algorithm");
		}
	};
}