#pragma once

#include <memory>
#include <optional>
#include "random.h"

enum GeneratorAlgorithmType {Voronoi, Delaunay, PolygonDivision};

class DungeonGeneratorSettings
{
private:
	Random::Seed seed;
	std::optional<std::string> path;
	unsigned int level;
	const GeneratorAlgorithmType generatorAlgorithmType;
	int roomCount;
public:
	DungeonGeneratorSettings(GeneratorAlgorithmType algorithmType, Random::Seed seed, std::optional<int> roomCount) 
		: seed{ seed }, generatorAlgorithmType(algorithmType), roomCount (roomCount.value()), level(0)
	{
		
	}


	Random::Seed getSeed() const					{ return seed; }
	GeneratorAlgorithmType getAlgorithmType() const { return generatorAlgorithmType; }
	int getRoomCount() const						{ return roomCount; }

	/*std::shared_ptr<MazeGeneratorSettings>				CreateMazeGeneratorSettings()
	{
		mazeGeneratorSettings = std::make_shared<MazeGeneratorSettings>(seed);
		return mazeGeneratorSettings;
	}*/

	//std::shared_ptr<MazeGeneratorSettings>			getMazeGeneratorSettings() { return mazeGeneratorSettings; }
};