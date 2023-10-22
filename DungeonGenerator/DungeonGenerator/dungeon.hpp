#pragma once
#include <vector>
#include "dungeonGenereatorSettings.hpp"
#include "dungeonData.hpp"

class Dungeon
{
private:
	Data::DungeonData dungeonData;
public:
	Dungeon();

	Data::DungeonData getData() const { return dungeonData; }

	void generate(DungeonGeneratorSettings  settings);
	void save(std::string path);
};