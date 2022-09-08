#pragma once

#include "component.hpp"
#include <vector>
#include "vector.hpp"

class Layout : public Component
{
private:
	int sides;

	std::vector<Math::NormalVector> wallNormals;
	std::vector<Math::Vec3>			points;

public:
	virtual void write(std::string path) override
	{

	}
};