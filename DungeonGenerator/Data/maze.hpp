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
		Math::Graph::Graph<int, Geometry::Edge> maze;	// maze, edges are the doors
		Math::Graph::Graph<int, Geometry::Edge> graph; // neighbours
	public:
		MazeData() = default;

		void setGraph(const Math::Graph::Graph<int, Geometry::Edge>& graph)
		{
			this->graph = graph;
		}

		void setMaze(const Math::Graph::Graph<int, Geometry::Edge>& graph)
		{
			this->maze = graph;
		}

		Math::Graph::Graph<int, Geometry::Edge> getMaze() const { return maze; }
		Math::Graph::Graph<int, Geometry::Edge> getGraph() const
		{ 
			return graph; 
		}
		std::vector<Geometry::Edge> getNotWallEdges() const;
	};
}

#endif