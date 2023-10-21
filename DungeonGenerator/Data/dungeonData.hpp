#ifndef DUNGEON_DATA_HPP
#define DUNGEON_DATA_HPP

#pragma once

#include "room.hpp"
#include "maze.hpp"
#include "data.hpp"
#include <random.h>
#include "layoutData.hpp"
#include "wallData.hpp"

namespace Data
{
	class DungeonData : public PersistentData
	{
	private:
		int version = 0;
		Random::Seed seed;

	private:
		int roomCount;
		std::vector<RoomData> rooms;
		MazeData mazeData;

		std::vector<LayoutData> floors;
		std::vector<WallData> walls;
	public:

		DungeonData() : seed(Random::GetSeed()) {}

		virtual std::string toString() const override
		{
			std::string result = "";
			result += std::to_string(version) + "\n";
			result += "DG\n";
			return result;
		}
		virtual ~DungeonData() override = default;

		void addRoom(const RoomData& room);

		int getVersion() const { return version; }
		unsigned int getSeed() const { return seed.getUnsignedValue(); }
		std::vector<LayoutData> getFloors() const;
		std::vector<WallData> getWalls() const;
	};
}


#endif
