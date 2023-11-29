#include "holeGenerator.hpp"

#include "log.h"
#include "guard.h"
#include "basicHoleGenerator.hpp"

namespace Generator
{
	HoleGenerator::HoleGenerator(const HoleGeneratorSettings& settings) : settings(settings)
	{
		switch (settings.getAlgorithmType())
		{
		case Basic:
			Log::info("Hole generation with Basic algorithm!");
			algorithm = std::make_shared<BasicHoleGenerator>();
			break;
		default:
			algorithm = nullptr;
		}
	}

	void HoleGenerator::generate(Data::DungeonData& dungeon)
	{
		TimeGuard timeGuard("Hole Generation");
		algorithm->Generate(dungeon);
		Log::info("Holes generated");
	}


}