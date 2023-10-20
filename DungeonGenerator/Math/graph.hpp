#ifndef GRAPH_HPP
#define GRAPH_HPP

#pragma once

#include <memory>

//#include "log.h"

#include <map>
#include <unordered_map>

#include "internalGraph.hpp"

namespace Math
{

	//enum InternalGraphType {LEMON};



	/*template<class Type>
	class Graph
	{
	private:
		InternalGraph* internalGraph;
		const InternalGraphType type;

	public:
		Graph(InternalGraphType type = InternalGraphType::LEMON) : type{type}
		{
			switch (this->type)
			{
				case LEMON:
					internalGraph = new LEMONGraph<Type>();
					break;
				default:
					Log::error("Unhandled Internal Graph Type!!");
					throw std::exception();
					break;
			}
		}
	};*/

	class Node
	{
	private:
	public:
		int id;
		Node(int id = -1) : id(id) {}

		bool operator== (const Node& other) const
		{
			return id == other.id;
		}
	};
}


namespace std
{
	template <>
	struct hash<Math::Node>
	{
		size_t operator()(const Math::Node& record) const
		{
			return hash<int>()(record.id);
		}
	};
}


namespace Math
{

	template<class Type>
	class Graph
	{
	private:
		std::unordered_map<Node, Type> values;
		std::unordered_map<Node, std::vector<Node>> neighbours;

		int maxId;

		Node getNodeFromValue(const Type& value) const;
		std::vector<Type> getValues(const std::vector<Node>& nodes) const;

	public:
		static const Node InvalidNode;

		Graph();

		bool containsValue(const Type& value) const;
		bool containsEdge(const Type& from, const Type& to) const;
			
		void addNode(const Type& value, bool forcedAdd = false);
		void addEdge(const Type& from, const Type& to, bool forcedAdd = false);

		std::unordered_map<Node, Type>				getNodes() const { return values; }
		std::unordered_map<Node, std::vector<Node>> getEdges() const { return neighbours; }


		template<class Type1, class Type2> 
		friend bool operator==(Graph<Type1> graph1, Graph<Type2> graph2);
	};

	
	template<class Type>
	const Node Graph<Type>::InvalidNode = Node(-1);

	template<class Type>
	Graph<Type>::Graph() : maxId(1)
	{

	}

	template<class Type>
	Node Graph<Type>::getNodeFromValue(const Type& value) const
	{
		for (const auto& [key, val] : values)
			if (value == val)
				return key;
		return Graph<Type>::InvalidNode;
	}

	template<class Type>
	bool Graph<Type>::containsValue(const Type& value) const
	{
		//TODO
		return false;
	}

	template<class Type>
	bool Graph<Type>::containsEdge(const Type& from, const Type& to) const
	{
		Node fromNode = getNodeFromValue(from);
		Node toNode = getNodeFromValue(to);

		try
		{
			std::vector<Node> nextNodes = neighbours.at(fromNode);
			return std::find(nextNodes.begin(), nextNodes.end(), toNode) != std::end(nextNodes);
		}
		catch (...)
		{
			return false;
		}
	}

	template<class Type>
	void Math::Graph<Type>::addNode(const Type& value, bool forcedAdd)
	{
		if (forcedAdd || !containsValue(value))
		{
			Node newNode(maxId);
			values[newNode] = value;
			++maxId;
		}

		//throw new std::exception("Can not add Node!");
	}

	template<class Type>
	void Graph<Type>::addEdge(const Type& from, const Type& to, bool forcedAdd)
	{
		if (forcedAdd || !containsEdge(from, to))
		{
			neighbours[getNodeFromValue(from)].push_back(getNodeFromValue(to));
		}

		//throw new std::exception("Can not add Edge!");
	}

	template<class Type1, class Type2>
	bool operator==(Graph<Type1> graph1, Graph<Type2> graph2)
	{
		if (!std::is_same<Type1, Type2>::value)
			return false;

		if (graph1.values != graph2.values)
			return false;

		if (graph1.neighbours != graph2.neighbours)
			return false;

		return true;
	}

}


#endif