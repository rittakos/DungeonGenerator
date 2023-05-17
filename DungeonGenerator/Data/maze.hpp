#ifndef MAZE_HPP
#define MAZE_HPP

#pragma once

#include <graph.hpp>

namespace Data
{
	class MazeData
	{
	private:
		Math::Graph<int> maze;
	public:
		MazeData() = default;
	};
}

#endif