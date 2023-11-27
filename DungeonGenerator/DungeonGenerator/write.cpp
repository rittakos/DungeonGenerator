#include "write.hpp"

namespace IO
{
	void write(const Data::RoomData& roomData, std::ofstream& os)
	{
		//os << "Room" << endOfLine;
		//os << roomData.getId() << endOfLine;

		write(roomData.getFloor(), os);

		for (const Data::WallData& wall : roomData.getWalls())
		{
			write(wall, os);
		}
	}

	void write(const Data::LayoutData& layout, std::ofstream& os)
	{
		os << "Floor" << endOfLine;
		os << layout.getPoints().size() << " " << layout.getTrianglesClockWise().size() + layout.getTrianglesCounterClockwise().size() << endOfLine;
		for (Math::Vec3f point : layout.getPoints())
		{
			os << point[0] << " " << point[1] << " " << point[2] << endOfLine;
		}

		for (Math::Vec3i triangle : layout.getTrianglesClockWise())
		{
			os << triangle[0] << " " << triangle[1] << " " << triangle[2] << endOfLine;
		}

		for (Math::Vec3i triangle : layout.getTrianglesCounterClockwise())
		{
			os << triangle[0] << " " << triangle[1] << " " << triangle[2] << endOfLine;
		}
	}

	void write(const Data::WallData& wall, std::ofstream& os)
	{
		os << "Wall" << endOfLine;
		os << wall.getPoints().size() << " " << wall.getTrianglesClockWise().size() + wall.getTrianglesCounterClockwise().size() << endOfLine;
		for (Math::Vec3f point : wall.getPoints())
		{
			os << point[0] << " " << point[1] << " " << point[2] << endOfLine;
		}

		for (Math::Vec3i triangle : wall.getTrianglesClockWise())
		{
			os << triangle[0] << " " << triangle[1] << " " << triangle[2] << endOfLine;
		}

		for (Math::Vec3i triangle : wall.getTrianglesCounterClockwise())
		{
			os << triangle[0] << " " << triangle[1] << " " << triangle[2] << endOfLine;
		}
	}
}