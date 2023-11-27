#include "basicHoleGenerator.hpp"

namespace Generator
{
	void BasicHoleGenerator::Generate(Data::DungeonData& dungeonData)
	{
		// MUST implement
		for (Data::LayoutData floor : dungeonData.getFloors())
		{
			Geometry::Polygon polygon = floor.getPolygon();
		}
	}
}