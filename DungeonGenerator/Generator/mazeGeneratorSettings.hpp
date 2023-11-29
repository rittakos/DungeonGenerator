#pragma once

#include "random.h"

enum MazeGeneratorType { Kruskal };

class MazeGeneratorSettings
{
private:
	MazeGeneratorType		type;

	Random::Seed seed;

public:
	explicit MazeGeneratorSettings(MazeGeneratorType algorithmType, Random::Seed seed) : seed{seed}, type(algorithmType) {}

	MazeGeneratorType getAlgorithmType() const { return type; }
};