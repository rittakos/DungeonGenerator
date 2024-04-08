#include "basicHoleGenerator.hpp"

namespace Generator
{
	void BasicHoleGenerator::Generate(Data::DungeonData& dungeonData)
	{
		for (Data::RoomData& room : dungeonData.getRooms())
		{
			Geometry::Polygon polygon = room.getFloor().getPolygon();
			if (!polygon.isConvex())
				continue;

			Geometry::Polygon hole;

			Math::Vec2f center;

			for (const Math::Vec2f& P : polygon.getPoints())
			{
				center += P;
			}
			center /= polygon.getPoints().size();

			for (const Math::Vec2f& P : polygon.getPoints())
			{
				Math::Vec2f newPoint = center + ((P - center) / 4.0f);
				hole.addPoint(newPoint);
			}

			polygon.addHole(hole);
			room.getFloor().setPolygon(polygon);
		}
	}
}