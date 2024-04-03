#include "dungeonData.hpp"

namespace Data
{
	DungeonData::DungeonData(const DungeonData& other) : DungeonData()
	{
		*this = other;
	}

	DungeonData& DungeonData::operator=(const DungeonData& other)
	{
		this->version = other.version;
		this->seed = other.seed;

		this->maze = other.maze;

		this->rooms = other.rooms;
		//this->walls = other.walls;
		//this->floors = other.floors;

		return *this;
	}

	void DungeonData::addRoom(const RoomData& room)
	{
		rooms.push_back(room);
	}

	std::vector<LayoutData> DungeonData::getFloors() const
	{
		std::vector<LayoutData> floors;

		for (const RoomData& room : rooms)
			floors.push_back(room.getFloorConst());

		return floors;
	}

	std::vector<WallData> DungeonData::getWalls() const
	{
		std::vector<WallData> walls;

		for (const RoomData& room : rooms)
		{
			for (const WallData& wall : room.getWalls())
			{
				//container.find(element) != container.end()
				//if(maze.getNotWallEdges().find(wall.getWallBase()) == maze.getNotWallEdges().end())
				std::vector<Geometry::Edge> wallsNotToInclude = maze.getNotWallEdges();
				if (std::find(wallsNotToInclude.begin(), wallsNotToInclude.end(), wall.getWallBase()) == std::end(wallsNotToInclude))
					walls.push_back(wall);
			}
		}

		return walls;
	}

}
