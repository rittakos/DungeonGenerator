#pragma once

#include "dungeonGenereatorSettings.hpp"
#include "dungeonData.hpp"
#include "generatorAlgorithm.hpp"


namespace Generator
{

	class DungeonGenerator
	{
	private:
		DungeonGeneratorSettings settings;
		std::shared_ptr<Generator::GeneratorAlgorithm> algorithm;
	public:
		DungeonGenerator(DungeonGeneratorSettings settings);

		void generate(Data::DungeonData& dungeonData);
	};

}