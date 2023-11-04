#pragma once

#include "generatorAlgorithm.hpp"

namespace Generator
{
	class KruskalGenerator : public MazeGeneratorAlgorithm
	{
	public:
		void Generate(Data::MazeData& mazeData) override;
	};
}