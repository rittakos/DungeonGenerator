#include "dungeonGenerator.hpp"

#include "delaunayGenerator.hpp"
#include "voronoiGenerator.hpp"
#include "log.h"
#include "guard.h"

namespace Generator
{
	DungeonGenerator::DungeonGenerator(DungeonGeneratorSettings settings) : settings{ settings }
	{
		switch (settings.getAlgorithmType())
		{
		case Voronoi:
			Log::info("Generation with Voronoi based algorithm!");
			algorithm = std::make_shared<Generator::VoronoiBasedGeneratorAlgorithm>();
			break;
		case Delaunay:
			Log::info("Generation with Delanuay based algorithm!");
			algorithm = std::make_shared<Generator::DelaunayBasedGeneratorAlgorithm>(settings);
			break;
		default:
			algorithm = nullptr;
		}
	}


	void DungeonGenerator::generate(Data::DungeonData& dungeonData)
	{
		TimeGuard timeGuard("Room Generation");
		algorithm->Generate(dungeonData);
		Log::info("Generation done!");
	}
}