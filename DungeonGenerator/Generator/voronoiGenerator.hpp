#pragma once

#include "generatorAlgorithm.hpp"

namespace Generator
{
	class VoronoiBasedGeneratorAlgorithm : public GeneratorAlgorithm
	{
	private:
		int width = 0;			// count of the horisontal cells
		int height = 0;			//count of the horisontal cells

		float maxRadius = 0;	// if the distance of a point is greater than this, 
		// than the point belong to an other point

		std::vector<Math::Vec3f> centers;

		const float epsilon = 0.0001f;

	private:
		bool equals(const Math::Vec2f& P1, const Math::Vec2f& P2) const;
		bool contains(const std::vector<Math::Vec2f>& vector, const Math::Vec2f& P) const;


	private:
		std::vector<Geometry::Line> getBisectors(const Math::Vec2i& coord, const Math::Vec2f& P) const;
		std::vector<Math::Vec2f>	getIntersectionPoints(const std::vector<Geometry::Line>& lines) const;
		std::vector<Math::Vec2f>	getCornersFromIntersectionPoints(	const std::vector<Math::Vec2f>& intersectionPoints,
																	const std::vector<Geometry::Line>& lines,
																	const Math::Vec2f& P,
																	const Math::Vec2i& coord) const;
		Geometry::Polygon			getPolyFromCorners(	const std::vector<Math::Vec2f>& corners,
														const std::vector<Geometry::Line>& lines,
														const Math::Vec2f& P) const;


		bool isConvex(std::vector<Math::Vec2f>& polygon) const;
		bool isValidTriangle(Math::Vec2f a, Math::Vec2f b, Math::Vec2f c) const;


		void getPolygons(std::vector<Math::Vec2f>& points) const;

		std::optional<Geometry::Polygon> getAllPolygons(std::vector<Math::Vec2f>& points) const;

		void generateCenters(const Math::Vec2f& cellSize, const Math::Vec3f& leftUpCorner);

		std::vector<Geometry::Polygon> generatePolygons();

	public:
		virtual ~VoronoiBasedGeneratorAlgorithm() = default;

		virtual void Generate(Data::DungeonData& dungeonData) override;
	};
}