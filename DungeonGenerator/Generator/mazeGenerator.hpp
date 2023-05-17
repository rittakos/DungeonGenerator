#pragma once

#include "mazeGeneratorSettings.hpp"

#include "log.h"

class MazeGenerator
{
public:
	MazeGenerator(MazeGeneratorSettings settings) {}

	void generate()
	{
		Log::info("Maze generated");
	}
};