#pragma once

#include <optional>
#include "random.h"

class GenerationSettings
{
private:
	std::optional<Random::Seed> seed;
	std::optional<std::string> path;
	float wallWidth;
	unsigned int level;

public:
	GenerationSettings();
	GenerationSettings(std::string path);

	void save(std::string path);
	void save();
};