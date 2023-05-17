#pragma once

#include "dungeon.hpp"
#include "room.hpp"
#include "generationSettings.hpp"


class GeneratorInterface
{
public:
	//virtual void generate(Dungeon& dungeon, const GenerationSettings& settings) const = 0;
	virtual void generate() const = 0;
};

namespace Room
{
	class RoomGenerator : GeneratorInterface
	{
	public:
		//virtual void generate(Room& room, const GenerationSettings& settings) const override = 0;
		virtual void generate() const override = 0;
	};

}


namespace Maze
{
	//class MazeGenerator : GeneratorInterface
	//{
	//public:
	//	//virtual void generate(Graph<Room::Room>& maze, const GenerationSettings& settings) const override = 0;
	//	virtual void generate() const override = 0;
	//};

	//class KruskalMazeGenerator final : public MazeGenerator
	//{
	//public:
	//	KruskalMazeGenerator()
	//	{

	//	}

	//	void generate() const override
	//	{

	//	}
	//	/*void generate(Graph<Room::Room>& maze, const GenerationSettings& settings) const
	//	{

	//	}*/
	//};

}
