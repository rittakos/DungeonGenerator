#pragma once
#include <vector>
#include "dungeonGenereatorSettings.hpp"
#include "mazeGeneratorSettings.hpp"
#include "dungeonData.hpp"

class Dungeon
{
private:
	Data::DungeonData dungeonData;
public:
	Dungeon();

	Data::DungeonData getData() const { return dungeonData; }

	void generateDungeon(const DungeonGeneratorSettings&  settings);
	void generateMaze(const MazeGeneratorSettings&  settings);
	void save(std::string path);
};