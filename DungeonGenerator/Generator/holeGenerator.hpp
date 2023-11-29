#pragma once

#include "holeGeneratorSettings.hpp"
#include "generatorAlgorithm.hpp"


namespace Generator
{

	class HoleGenerator
	{
		std::shared_ptr<Generator::HoleGeneratorAlgorithm> algorithm;
		HoleGeneratorSettings settings;

	public:
		HoleGenerator(const HoleGeneratorSettings& settings);

		void generate(Data::DungeonData& dungeon);
	};

}