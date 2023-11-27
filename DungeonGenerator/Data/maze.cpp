#include "maze.hpp"

namespace Data
{
	std::vector<Geometry::Edge> MazeData::getNotWallEdges() const
	{
		return maze.getEdgeValues();
	}
}