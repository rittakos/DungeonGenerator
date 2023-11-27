#include "room.hpp"

namespace Data
{
	int RoomData::nextId = 0;

	RoomData::RoomData(const Geometry::Polygon& polygon) : id(nextId), floor(polygon)
	{
		++RoomData::nextId;

		std::vector<Math::Vec3f> points = floor.getPoints();
		for (int idx = 0; idx < points.size() - 1; ++idx)
		{
			walls.push_back(Data::WallData(points[idx], points[idx + 1]));
		}
		walls.push_back(Data::WallData(points[points.size() - 1], points[0]));
	}

	RoomData& RoomData::operator=(const RoomData& other)
	{
		return *this;
	}

}
