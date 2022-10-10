#pragma once
#include <vector>
#include "room.hpp"
#include "maze.hpp"

class Dungeon
{
private:
	bool saved;
	std::vector<Room> rooms;
	Maze maze;
public:
	Dungeon();
	void save();
};