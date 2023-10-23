#pragma once
#include <algorithm>
#include "dungeonData.hpp"

namespace Generator
{
	class GeneratorAlgorithm
	{
	public:
		virtual void Generate(Data::DungeonData& dungeonData) = 0;

		virtual ~GeneratorAlgorithm() = default;
	};


	class MazeGeneratorAlgorithm
	{
	public:
		virtual void Generate() = 0;

		virtual ~MazeGeneratorAlgorithm() = default;
	};
}