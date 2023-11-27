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
	explicit MazeGeneratorSettings(MazeGeneratorType algorithmType, unsigned int seed) : seed{seed}, hardness(Easy), type(algorithmType) {}

	MazeGeneratorType getAlgorithmType() const { return type; }
};