#pragma once

#include "generatorAlgorithm.hpp"
#include "dungeonGenereatorSettings.hpp"
#include "delaunayBase.hpp"

namespace Generator
{

	// https://en.wikipedia.org/wiki/Delaunay_triangulation
	class DelaunayBasedGeneratorAlgorithm final : public GeneratorAlgorithm
	{
	private:
		const unsigned int pointCount;
		std::vector<Math::Vec2f> points;
		Geometry::Delaunay::DelaunayTriangulation triangulation;

		void generatePoints();
		std::vector<Geometry::Polygon> createPolygons(const Geometry::Delaunay::DelaunayTriangulation& triangulation) const;

		Math::Vec2f calcOutterCircleCenter(const Geometry::Delaunay::Triangle& triangle) const;
		Math::Angle getSumAngleAroundPoint(int pointIdx, const std::vector<Geometry::Delaunay::Triangle>& trainglesAround) const;
		Math::Angle getAngleOfTriangle(const Geometry::Delaunay::Triangle& triangle, int pointIdx) const;

	public:
		DelaunayBasedGeneratorAlgorithm(const DungeonGeneratorSettings& settings);

		virtual void Generate(Data::DungeonData& dungeonData) override;

		virtual ~DelaunayBasedGeneratorAlgorithm() = default;
	};

}