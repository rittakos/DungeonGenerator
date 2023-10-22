#pragma once

class InternalGraph
{
public:
	virtual void addNode() = 0;
	virtual void addEdge() = 0;
	virtual void listNodes() = 0;

	virtual ~InternalGraph() = default;
};