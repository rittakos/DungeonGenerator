#ifndef ROOM_H
#define ROOM_H

#pragma once

#include <vector>

#include "layoutData.hpp"
#include "wallData.hpp"

namespace Data
{

	class RoomData
	{
	private:
		static int nextId;

		const int id; //0, 1... unique

		LayoutData floor;
		std::vector<WallData> walls;
	public:
		RoomData(const Geometry::Polygon& polygon);

		LayoutData				getFloor() const { return floor; }
		std::vector<WallData>	getWalls() const { return walls; }

		int getId() const { return id; }
	};

}


#endif