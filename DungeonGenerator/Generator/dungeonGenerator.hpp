#pragma once

#include "dungeonGenereatorSettings.hpp"
#include "dungeonData.hpp"
#include "polygonGenerator.hpp"
#include "delaunay.hpp"
//#include <mazeGenerator.hpp>
#include "log.h"
#include <guard.h>


class DungeonGenerator
{
private:
	DungeonGeneratorSettings settings;
	std::shared_ptr<Generator::GeneratorAlgorithm> algorithm;
public:
	DungeonGenerator(DungeonGeneratorSettings settings) : settings{ settings }
	{
		switch (settings.getAlgorithmType())
		{
		case Voronoi:
			Log::info("Generation with Voronoi based algorithm!");
			algorithm = std::make_shared<Generator::VoronoiBasedGeneratorAlgorithm>();
			break;
		case Delaunay:
			Log::info("Generation with Delanuay based algorithm!");
			algorithm = std::make_shared<Generator::DelaunayBasedGeneratorAlgorithm>();
			break;
		default:
			algorithm = nullptr;
		}
	}
	void generate(Data::DungeonData& dungeonData)
	{
		/*MazeGenerator mazeGenerator(*settings.getMazeGeneratorSettings());
		mazeGenerator.generate();*/
		/*Generator::PolygonGenerator polygonGenerator(5);
		Data::LayoutData layout(polygonGenerator.generate());
		dungeonData.floors.push_back(layout);
		Log::info("Dungeon Generated");*/
		TimeGuard timeGuard("Generation");
		algorithm->Generate(dungeonData);
		Log::info("Generation done!");
	}
};