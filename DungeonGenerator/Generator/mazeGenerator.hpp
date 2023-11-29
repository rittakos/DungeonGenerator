#pragma once

#include "mazeGeneratorSettings.hpp"
#include "generatorAlgorithm.hpp"


namespace Generator
{

	class MazeGenerator
	{
		std::shared_ptr<Generator::MazeGeneratorAlgorithm> algorithm;
		MazeGeneratorSettings settings;

	public:
		MazeGenerator(const MazeGeneratorSettings& settings);
		
		void generate(Data::MazeData& maze);
	};

}