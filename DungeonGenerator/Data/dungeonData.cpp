#include "dungeonData.hpp"

namespace Data
{

	void DungeonData::addRoom(const RoomData& room)
	{
		rooms.push_back(room);
	}

	std::vector<LayoutData> DungeonData::getFloors() const
	{
		std::vector<LayoutData> floors;

		for (const RoomData& room : rooms)
			floors.push_back(room.getFloor());

		return floors;
	}

	std::vector<WallData> DungeonData::getWalls() const
	{
		std::vector<WallData> walls;

		for (const RoomData& room : rooms)
		{
			for (const WallData& wall : room.getWalls())
			{
				walls.push_back(wall);
			}
		}

		return walls;
	}

}
