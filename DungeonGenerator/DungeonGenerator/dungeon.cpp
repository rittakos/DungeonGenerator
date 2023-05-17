#include "dungeon.hpp"
#include "dungeonWriter.hpp"
#include <dungeonGenerator.hpp>
#include <log.h>


Dungeon::Dungeon()
{
}

void Dungeon::generate(DungeonGeneratorSettings settings)
{
	DungeonGenerator generator(settings);
	generator.generate(dungeonData);
}

void Dungeon::save(std::string path)
{
	IO::DungeonWriter writer(dungeonData, path);
	writer.write();
}
