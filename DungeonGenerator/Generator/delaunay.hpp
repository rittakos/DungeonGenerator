#pragma once

#include "generatorAlgorithm.hpp"

namespace Generator
{

	// https://en.wikipedia.org/wiki/Delaunay_triangulation
	class DelaunayBasedGeneratorAlgorithm : public GeneratorAlgorithm
	{
	private:
		const unsigned int pointCount;
		std::vector<Math::Vec2f> points;

	public:
		virtual void Generate(Data::DungeonData& dungeonData) override;
	};

}