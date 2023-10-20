#include "dungeonWriter.hpp"
#include "fstream"
#include "cassert"
#include "log.h"

namespace IO
{

	DungeonWriter::DungeonWriter(const Data::DungeonData& dungeonData, std::string path) : file(path, std::ofstream::out), data(dungeonData)
	{
		assert(file.is_open());
		if (!file.is_open())
			Log::error("Can not open file!");
	}

	DungeonWriter::~DungeonWriter()
	{
		if(file.is_open())
			file.close();
	}

	void DungeonWriter::write()
	{
		if (!file.is_open())
			return;

		file << data.getVersion () << endOfLine;
		file << data.getSeed () << endOfLine;

		writeFloors();
		writeWalls();

		file << "End" << endOfLine;

		file.close();

		Log::info("File saved!");
	}

	void DungeonWriter::writeFloors()
	{
		for (Data::LayoutData& layout : data.getFloors())
		{
			file << "Floor" << endOfLine;
			file << layout.getPoints().size() << " " << layout.getTrianglesClockWise().size() + layout.getTrianglesCounterClockwise().size() << endOfLine;
			for (Math::Vec3f point : layout.getPoints())
			{
				file << point[0] << " " << point[1] << " " << point[2] << endOfLine;
			}

			for (Math::Vec3i triangle : layout.getTrianglesClockWise())
			{
				file << triangle[0] << " " << triangle[1] << " " << triangle[2] << endOfLine;
			}

			for (Math::Vec3i triangle : layout.getTrianglesCounterClockwise())
			{
				file << triangle[0] << " " << triangle[1] << " " << triangle[2] << endOfLine;
			}
		}
	}

	void DungeonWriter::writeWalls()
	{
		for (Data::WallData& wall : data.getWalls())
		{
			file << "Wall" << endOfLine;
			file << wall.getPoints().size() << " " << wall.getTrianglesClockWise().size() + wall.getTrianglesCounterClockwise().size() << endOfLine;
			for (Math::Vec3f point : wall.getPoints())
			{
				file << point[0] << " " << point[1] << " " << point[2] << endOfLine;
			}

			for (Math::Vec3i triangle : wall.getTrianglesClockWise())
			{
				file << triangle[0] << " " << triangle[1] << " " << triangle[2] << endOfLine;
			}

			for (Math::Vec3i triangle : wall.getTrianglesCounterClockwise())
			{
				file << triangle[0] << " " << triangle[1] << " " << triangle[2] << endOfLine;
			}
		}
	}

}
