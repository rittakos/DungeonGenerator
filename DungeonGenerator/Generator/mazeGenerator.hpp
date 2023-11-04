#pragma once

#include "mazeGeneratorSettings.hpp"
#include "generatorAlgorithm.hpp"

#include "log.h"
#include <guard.h>
#include "kruskalGenerator.hpp"

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
				algorithm = std::make_shared<KruskalGenerator>();
				break;
			default:
				algorithm = nullptr;
			}
		}



		void generate(Data::MazeData& maze)
		{
			TimeGuard timeGuard("Maz Generation");
			algorithm->Generate(maze);
			Log::info("Maze generated");
		}
	};

}