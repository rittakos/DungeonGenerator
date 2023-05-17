#pragma once
#include <vector>
#include "room.hpp"
#include "maze.hpp"
#include <polygon.hpp>
#include "roomSystem.hpp"
#include "generationSettings.hpp"
#include "dungeonGenereatorSettings.hpp"
#include "dungeonData.hpp"

class Dungeon
{
private:
	//bool saved;
	//std::vector<Room> rooms;
	RoomSystem rooms;
	//Data::MazeData maze;
	Data::DungeonData dungeonData;

	std::shared_ptr<Layout> layout;
public:
	Dungeon();

	Data::DungeonData getData() const { return dungeonData; }

	void generate(DungeonGeneratorSettings  settings);
	void save(std::string path);
};