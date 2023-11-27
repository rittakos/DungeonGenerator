#pragma once
#include <vector>
#include "dungeonGenereatorSettings.hpp"
#include "mazeGeneratorSettings.hpp"
#include "dungeonData.hpp"
#include <holeGeneratorSettings.hpp>

class Dungeon
{
private:
	Data::DungeonData dungeonData;
public:
	Dungeon();

	Data::DungeonData getData() const { return dungeonData; }

	void generateDungeon(const DungeonGeneratorSettings&  settings);
	void generateMaze(const MazeGeneratorSettings&  settings);
	void generateHoles(const HoleGeneratorSettings&  settings);
	void save(std::string path);
};