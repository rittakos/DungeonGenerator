#pragma once
#include <algorithm>
#include "dungeonData.hpp"

namespace Generator
{
	template<class Point>
	class ControlPointGenerator
	{
	public:
		virtual std::vector<Point> generate() const = 0;
	};

	class DungeonGeneratorAlgorithm
	{
	public:
		virtual void Generate(Data::DungeonData& dungeonData) = 0;

		virtual ~DungeonGeneratorAlgorithm() = default;
	};


	class MazeGeneratorAlgorithm
	{
	public:
		virtual void Generate(Data::MazeData& mazeData) = 0;

		virtual ~MazeGeneratorAlgorithm() = default;
	};

	class HoleGeneratorAlgorithm
	{
	public:
		virtual void Generate(Data::DungeonData& dungeonData) = 0;

		virtual ~HoleGeneratorAlgorithm() = default;
	};
}