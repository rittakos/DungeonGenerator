#pragma once

#include "random.h"

enum HoleGeneratorType { Basic };

class HoleGeneratorSettings
{
private:
	HoleGeneratorType	type;
	Random::Seed		seed;

public:
	explicit HoleGeneratorSettings(HoleGeneratorType algorithmType, Random::Seed seed) : seed{ seed }, type(algorithmType) {}

	HoleGeneratorType getAlgorithmType() const { return type; }
};