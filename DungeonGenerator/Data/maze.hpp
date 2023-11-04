#ifndef MAZE_HPP
#define MAZE_HPP

#pragma once

#include <set>

#include <graph.hpp>
#include <edge.hpp>

namespace Data
{
	class MazeData
	{
	private:
		Math::Graph<int> maze;
		Math::Graph<int, Geometry::Edge> graph;
	public:
		MazeData() = default;

		void setGraph(const Math::Graph<int, Geometry::Edge>& graph)
		{
			this->graph = graph;
		}

		Math::Graph<int> getMaze() const { return maze; }
		std::vector<Geometry::Edge> getNotWallEdges() const;
	};
}

#endif