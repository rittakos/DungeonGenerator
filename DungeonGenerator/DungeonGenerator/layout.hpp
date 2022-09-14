#pragma once

#include "component.hpp"
#include <vector>
#include "line.hpp"
//#include "vector.hpp"

class Layout : public Component
{
private:
	std::vector<std::shared_ptr<Geometry::Line>> sides;

public:
	virtual void write(std::string path) override
	{

	}
};