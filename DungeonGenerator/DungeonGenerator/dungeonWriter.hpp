#pragma once
#include <fstream>
#include <dungeonData.hpp>

namespace IO
{

	class DungeonWriter
	{
	private:
		std::ofstream file;
		Data::DungeonData data;

		const std::string endOfLine = "\n";
	public:
		DungeonWriter(const Data::DungeonData& dungeonData, std::string path);
		~DungeonWriter();

		void write();
		void writeFloors();
		void writeWalls();
	};
}