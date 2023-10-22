#include "dungeonWriter.hpp"
#include "fstream"
#include "cassert"
#include "log.h"

#include "write.hpp"

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
			IO::write(layout, file);
		}
	}

	void DungeonWriter::writeWalls()
	{
		for (Data::WallData& wall : data.getWalls())
		{
			IO::write(wall, file);
		}
	}

}
