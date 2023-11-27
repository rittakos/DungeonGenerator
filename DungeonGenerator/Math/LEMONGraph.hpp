#pragma once

#include "lemon/list_graph.h"

//using: http://lemon.cs.elte.hu/trac/lemon

// LOW lemon graph eltavolitasa?

//undirected
template<class Type>
class LEMONGraph final //: public InternalGraph
{
private:
	lemon::ListGraph::NodeMap<Type>* nodeMap;
	lemon::ListGraph* graph;
	std::vector<lemon::ListDigraph::Arc> edges;
public:
	
	LEMONGraph() 
	{
		graph = new lemon::ListGraph();
		nodeMap = new lemon::ListGraph::NodeMap<Type>(*graph);
		//Log::info("Graph (LEMON) Created!");
	}

	~LEMONGraph()
	{
		delete graph;
		delete nodeMap;
	}

	/*void f()
	{
		lemon::ListGraph graph;
		graph.addNode();
		lemon::ListGraph::NodeMap<int> nodeIds(graph);
	}*/

	void addNode(const Type& value) override
	{
		lemon::ListGraph::Node newNode = graph->addNode();
		(*nodeMap)[newNode] = value;
		
		/*lemon::ListGraph::Node newNode = graph->addNode();
		(*nodeIds)[newNode] = lemon::countNodes<lemon::ListGraph>(*graph);*/
	}

	void addEdge(const Type& value1, const Type& value2) override
	{
		lemon::ListGraph::Node N1;
		lemon::ListGraph::Node N2;


		/*for (lemon::ListGraph::NodeIt u(*graph); u != lemon::INVALID; ++u)
		{
			lemon::ListGraph::Node N = u;
			if ((*nodeMap)[N] == value1)
				N1 = u;
			if ((*nodeMap)[N] == value2)
				N2 = u;
		}*/


		graph->addEdge(N1, N2);
		//graph.addEdge();
	}

	void listNodes() override
	{
		/*for (lemon::ListGraph::NodeIt n(graph); n != lemon::INVALID; ++n)
			std::cout << nodeMap[n] << std::endl;*/
	}
};