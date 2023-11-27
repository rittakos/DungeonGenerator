#pragma once

#include "generatorAlgorithm.hpp"

namespace Generator
{
	class BasicHoleGenerator : public HoleGeneratorAlgorithm
	{
	public:
		void Generate(Data::DungeonData& dungeonData) override;
	};
}