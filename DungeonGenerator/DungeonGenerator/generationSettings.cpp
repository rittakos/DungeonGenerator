#include "generationSettings.hpp"
#include <chrono>

GenerationSettings::GenerationSettings() : fixSeed{false}
{
	generateSeed();
}

void GenerationSettings::setFixSeed(int seed)
{
	this->fixSeed = true;
	this->seed = seed;
}

void GenerationSettings::generateSeed()
{
	seed = static_cast<long>(std::time(0));
}

int GenerationSettings::getSeed() const
{
	return seed;
}
