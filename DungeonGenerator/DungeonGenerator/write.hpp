#pragma once

#include "room.hpp"
#include <fstream>


namespace IO
{
	const std::string endOfLine = "\n";

	void write(const Data::RoomData& room, std::ofstream& os);
	void write(const Data::LayoutData& layout, std::ofstream& os);
	void write(const Data::WallData& wall, std::ofstream& os);
}