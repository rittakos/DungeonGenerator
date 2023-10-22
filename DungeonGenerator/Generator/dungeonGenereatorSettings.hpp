#pragma once

#include <memory>
#include <optional>
#include "random.h"

enum GeneratorAlgorithmType {Voronoi, Delaunay, PolygonDivision};

class DungeonGeneratorSettings
{
private:
	//std::shared_ptr<RoomsGeneratorSettings> roomsGeneratorSettings;
	//std::shared_ptr<MazeGeneratorSettings> mazeGeneratorSettings;
	//std::optional<std::shared_ptr<RoomInternalGeneratorSettings>> roomInternalGeneratorSettings;

	Random::Seed seed;
	std::optional<std::string> path;
	//float wallWidth;
	unsigned int level;
	const GeneratorAlgorithmType generatorAlgorithmType;
	int roomCount;
public:
	DungeonGeneratorSettings(GeneratorAlgorithmType algorithmType, unsigned int seed, std::optional<int> roomCount) 
		: seed{ seed }, generatorAlgorithmType(algorithmType), roomCount (roomCount.value()), level(0)
	{
		
	}
	//DungeonGeneratorSettings() : seed(){}


	Random::Seed getSeed() const					{ return seed; }
	GeneratorAlgorithmType getAlgorithmType() const { return generatorAlgorithmType; }
	int getRoomCount() const						{ return roomCount; }

	//std::shared_ptr<RoomsGeneratorSettings>			CreateRoomsGenerationSettings();
	//std::shared_ptr<RoomInternalGeneratorSettings>	CreateRoomInternalGeneratorSettings();
	/*std::shared_ptr<MazeGeneratorSettings>				CreateMazeGeneratorSettings()
	{
		mazeGeneratorSettings = std::make_shared<MazeGeneratorSettings>(seed);
		return mazeGeneratorSettings;
	}*/

	//std::shared_ptr<MazeGeneratorSettings>			getMazeGeneratorSettings() { return mazeGeneratorSettings; }
};