#pragma once

#include "dungeon.hpp"
#include "room.hpp"
#include "graph.hpp"
#include "generationSettings.hpp"


class Generator
{
public:
	virtual void generate(Dungeon& dungeon, const GenerationSettings& settings) const = 0;
};

namespace Room
{
	class RoomGenerator
	{
	public:
		virtual void generate(Room& room, const GenerationSettings& settings) const = 0;
	};

}


namespace Maze
{
	class MazeGenerator
	{
	public:
		virtual void generate(Graph<Room::Room>& maze, const GenerationSettings& settings) const = 0;
	};

}
