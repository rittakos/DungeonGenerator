#pragma once

#include "internalGraph.hpp"

#include "lemon/list_graph.h"

//using: http://lemon.cs.elte.hu/trac/lemon

//undirected
template<class Type>
class LEMONGraph final : public InternalGraph
{
private:
	lemon::ListGraph::NodeMap<Type>* nodeIds;
	lemon::ListGraph* graph;
public:
	
	LEMONGraph() 
	{
		graph = new lemon::ListGraph();
		//Log::info("Graph (LEMON) Created!");
	}

	~LEMONGraph()
	{
		delete graph;
	}

	/*void f()
	{
		lemon::ListGraph graph;
		graph.addNode();
		lemon::ListGraph::NodeMap<int> nodeIds(graph);
	}*/

	virtual void addNode() override
	{
		
		/*lemon::ListGraph::Node newNode = graph->addNode();
		(*nodeIds)[newNode] = lemon::countNodes<lemon::ListGraph>(*graph);*/
	}

	virtual void addEdge() override
	{
		//graph.addEdge();
	}

	virtual void listNodes() override
	{
		//for (lemon::ListGraph::NodeIt n(graph); n != lemon::INVALID; ++n)
			//std::cout << nodeIds[n] << std::endl;
	}
};