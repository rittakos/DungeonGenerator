#ifndef DUNGEON_DATA_HPP
#define DUNGEON_DATA_HPP

#pragma once

#include "room.hpp"
#include "maze.hpp"
#include <random.h>
#include "layoutData.hpp"
#include "wallData.hpp"
#include <string>

namespace Data
{
	class DungeonData
	{
	private:
		int version = 0;
		Random::Seed seed;

	private:
		//int roomCount;
		std::vector<RoomData> rooms;
		MazeData maze;

		std::vector<LayoutData> floors;
		std::vector<WallData> walls;
	public:

		DungeonData() : seed(Random::GetSeed()) {}

		DungeonData(const DungeonData& other);
		DungeonData& operator=(const DungeonData& other);

		std::string toString() const
		{
			std::string result = "";
			result += std::to_string(version) + "\n";
			result += "DG\n";
			return result;
		}

		void addRoom(const RoomData& room);

		MazeData& getMaze() { return maze; }

		int getVersion() const { return version; }
		unsigned int getSeed() const { return seed.getUnsignedValue(); }

		std::vector<RoomData>& getRooms() { return rooms; }
		std::vector<LayoutData> getFloors() const;
		std::vector<WallData> getWalls() const;
	};
}


#endif
