#pragma once

#include "mazeGeneratorSettings.hpp"
#include "generatorAlgorithm.hpp"

#include "log.h"

namespace Generator
{

	class MazeGenerator
	{
		std::shared_ptr<Generator::MazeGeneratorAlgorithm> algorithm;
		MazeGeneratorSettings settings;

	public:
		MazeGenerator(const MazeGeneratorSettings& settings) : settings (settings) 
		{
			switch (settings.getAlgorithmType())
			{
			case Kruskal:
				Log::info("Maze generation with Kruskal based algorithm!");
				//algorithm = std::make_shared<>();
				break;
			default:
				algorithm = nullptr;
			}
		}



		void generate()
		{
			algorithm->Generate();
			Log::info("Maze generated");
		}
	};

}