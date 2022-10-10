#pragma once
#include <string>
#include <vector>
//#include "vector.hpp"
#include "layout.hpp"
#include "component.hpp"
#include <memory>

namespace Room
{
	class Room
	{
	private:

		std::shared_ptr<Layout> layout;

		std::vector<std::shared_ptr<Component>> components;

	public:

		Room();

		void save(std::string path);
	};
}

