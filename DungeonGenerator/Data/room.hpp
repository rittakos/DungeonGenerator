#ifndef ROOM_H
#define ROOM_H

#pragma once

#include "polygon.hpp"
#include <optional>
#include "roomDescription.hpp"

namespace Data
{

	class RoomData
	{
	private:
		int id; //0, 1...
		std::optional<RoomDescriptionData> roomDescription;
	public:
		RoomData();
	};

}

#endif