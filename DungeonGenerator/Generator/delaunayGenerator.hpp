#pragma once

#include "generatorAlgorithm.hpp"
#include "dungeonGenereatorSettings.hpp"
#include "delaunay.hpp"

namespace Generator
{

	// https://en.wikipedia.org/wiki/Delaunay_triangulation
	class DelaunayBasedGeneratorAlgorithm : public GeneratorAlgorithm
	{
	private:
		const unsigned int pointCount;
		std::vector<Math::Vec2f> points;

		void generatePoints();
		std::vector<Geometry::Polygon> createPolygons(const Geometry::Delaunay::DelaunayTriangulation& triangulation) const;

		Math::Vec2f calcOutterCircleCenter(const Geometry::Delaunay::Triangle& triangle) const;

	public:
		DelaunayBasedGeneratorAlgorithm(const DungeonGeneratorSettings& settings);

		virtual void Generate(Data::DungeonData& dungeonData) override;
	};

}