#pragma once

#include "random.h"

enum MazeGeneratorType { Kruskal };
enum MazeGeneratorHardness { Easy, Medium, Hard };

class MazeGeneratorSettings
{
private:
	MazeGeneratorType		type;
	MazeGeneratorHardness	hardness;

	Random::Seed seed;

public:
	MazeGeneratorSettings(Random::Seed seed) : seed{seed} {}
};