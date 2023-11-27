#include "mazeGenerator.hpp"

#include "log.h"
#include <guard.h>
#include "kruskalGenerator.hpp"

namespace Generator
{

	MazeGenerator::MazeGenerator(const MazeGeneratorSettings& settings) : settings(settings)
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

	void MazeGenerator::generate(Data::MazeData& maze)
	{
		TimeGuard timeGuard("Maz Generation");
		algorithm->Generate(maze);
		Log::info("Maze generated");
	}

}
