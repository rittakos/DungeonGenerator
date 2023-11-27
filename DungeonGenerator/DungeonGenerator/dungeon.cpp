#include "dungeon.hpp"
#include "dungeonWriter.hpp"
#include "dungeonGenerator.hpp"
#include "mazeGenerator.hpp"
#include <holeGenerator.hpp>


Dungeon::Dungeon()
{
}

void Dungeon::generateDungeon(const DungeonGeneratorSettings& settings)
{
	Generator::DungeonGenerator generator(settings);
	generator.generate(dungeonData);
}

void Dungeon::generateMaze(const MazeGeneratorSettings& settings)
{
	Generator::MazeGenerator generator(settings);
	generator.generate(dungeonData.getMaze());
}

void Dungeon::generateHoles(const HoleGeneratorSettings& settings)
{
	Generator::HoleGenerator generator(settings);
	generator.generate(dungeonData);
}

void Dungeon::save(std::string path)
{
	IO::DungeonWriter writer(dungeonData, path);
	writer.write();
}
