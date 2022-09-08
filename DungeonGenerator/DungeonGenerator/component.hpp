#pragma once
#include <string>

class Component
{
public:
	virtual void write(std::string path) = 0;
};

class GraphicsComponent
{
public:
	virtual void rotate() = 0;
	virtual void write(std::string path) = 0;
};