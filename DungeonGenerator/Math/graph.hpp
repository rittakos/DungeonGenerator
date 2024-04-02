#ifndef GRAPH_HPP
#define GRAPH_HPP

#pragma once

#include <map>
#include <memory>
#include <optional>
#include <set>
#include <unordered_map>


namespace Math
{

	class Node
	{
	public:
		//const int id;
		int id;
		explicit Node(int id = -1) : id(id) {}

		bool operator== (const Node& other) const
		{
			return id == other.id;
		}
	};

	class Edge
	{
	private:
		//const Node from;
		Node from;
		//const Node to;
		Node to;


	public:
		//const int id;
		int id;

		Edge(Node from, Node to, int id = -1) : from(from), to(to), id(id) {}

		bool operator== (const Edge& other) const
		{
			return from == other.from && to == other.to;
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

	template <>
	struct hash<Math::Edge>
	{
		size_t operator()(const Math::Edge& record) const
		{
			return hash<int>()(record.id);
		}
	};
}


namespace Math
{

	template<class NodeType, class EdgeType = int>
	class Graph
	{
	private:
		std::unordered_map<Node, NodeType> values;
		std::unordered_map<Edge, std::optional<EdgeType>> edgeValues;

		std::unordered_map<Node, std::vector<Node>> neighbours;

		int maxId;

		Node getNodeFromValue(const NodeType& value) const;
		std::vector<NodeType> getValues(const std::vector<Node>& nodes) const;

	public:
		static const Node InvalidNode;

		Graph();
		~Graph();

		Graph(const Graph& other);
		Graph<NodeType, EdgeType>& operator=(const Graph<NodeType, EdgeType>& other);

		bool containsValue(const NodeType& value) const;
		bool containsEdge(const NodeType& from, const NodeType& to) const;
			
		void addNode(const NodeType& value, bool forcedAdd = false);
		void addEdge(const NodeType& from, const NodeType& to, std::optional<EdgeType> edgeValue = {}, bool forcedAdd = false);
		// TODO addEdges from Nodes

		void removeEdge(const NodeType& from, const NodeType& to);

		std::unordered_map<Node, NodeType>					getNodes() const 
		{ 
			return values; 
		}
		std::unordered_map<Node, std::vector<Node>>			getEdges() const 
		{ 
			return neighbours; 
		}
		std::vector<EdgeType>								getEdgeValues() const;
		std::unordered_map<Edge, std::optional<EdgeType>>	getEdgesWithValues() const 
		{ 
			return edgeValues; 
		}


		template<class NodeType1, class EdgeType1>
		friend bool operator==(Graph<NodeType1, EdgeType1> graph1, Graph<NodeType1, EdgeType1> graph2);
	};

	
	template<class NodeType, class EdgeType>
	const Node Graph<NodeType, EdgeType>::InvalidNode = Node(-1);

	template<class NodeType, class EdgeType>
	Graph<NodeType, EdgeType>::Graph() : maxId(1)
	{

	}

	template<class NodeType, class EdgeType /*= int*/>
	Math::Graph<NodeType, EdgeType>::Graph (const Graph& other) : Graph()
	{
		*this = other;
	}

	template<class NodeType, class EdgeType /*= int*/>
	Math::Graph<NodeType, EdgeType>::~Graph ()
	{

	}

	template<class NodeType, class EdgeType>
	Graph<NodeType, EdgeType>& Graph<NodeType, EdgeType>::operator=(const Graph<NodeType, EdgeType>& other)
	{
		maxId = other.maxId;

		for (auto& [key, value] : other.values)
			values[key] = value;

		for (auto& [key, value] : other.edgeValues)
			edgeValues[key] = value;

		for (auto& [key, value] : other.neighbours)
			neighbours[key] = value;

		return *this;
	}

	template<class NodeType, class EdgeType>
	std::vector<EdgeType>	Graph<NodeType, EdgeType>::getEdgeValues() const
	{
		std::vector<EdgeType> values;
		for (const auto& [key, val] : edgeValues)
			if(std::find(values.begin(), values.end(), val.value()) == std::end(values))
				values.push_back(val.value());
		return values;
	}

	template<class NodeType, class EdgeType>
	Node Graph<NodeType, EdgeType>::getNodeFromValue(const NodeType& value) const
	{
		for (const auto& [key, val] : values)
			if (value == val)
				return key;
		return Graph<NodeType>::InvalidNode;
	}

	template<class NodeType, class EdgeType>
	bool Graph<NodeType, EdgeType>::containsValue(const NodeType& value) const
	{
		//TODO
		return false;
	}

	template<class NodeType, class EdgeType>
	bool Graph<NodeType, EdgeType>::containsEdge(const NodeType& from, const NodeType& to) const
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

	template<class NodeType, class EdgeType>
	void Graph<NodeType, EdgeType>::addNode(const NodeType& value, bool forcedAdd)
	{
		if (forcedAdd || !containsValue(value))
		{
			Node newNode(maxId);
			values[newNode] = value;
			++maxId;
		}

		//throw new std::exception("Can not add Node!");
	}

	template<class NodeType, class EdgeType>
	void Graph<NodeType, EdgeType>::addEdge(const NodeType& from, const NodeType& to, std::optional<EdgeType> edgeValue, bool forcedAdd)
	{
		if (forcedAdd || !containsEdge(from, to))
		{
			neighbours[getNodeFromValue(from)].push_back(getNodeFromValue(to));
			Edge newEdge(getNodeFromValue(from), getNodeFromValue(to));
			edgeValues[newEdge] = edgeValue;

		}

		//throw new std::exception("Can not add Edge!");
	}

	template<class NodeType, class EdgeType>
	void Graph<NodeType, EdgeType>::removeEdge(const NodeType& from, const NodeType& to)
	{
		if (containsEdge(from, to))
		{
			neighbours[getNodeFromValue(from)].push_back(getNodeFromValue(to));
			std::vector<NodeType> n = neighbours[getNodeFromValue(from)];
			n.erase(std::remove(n.begin(), n.end(), to), n.end());

			if (n.empty())
				neighbours.erase(getNodeFromValue(from));

			Edge edge(getNodeFromValue(from), getNodeFromValue(to));
			edgeValues.erase(edge);

		}
	}

	template<class NodeType, class EdgeType>
	bool operator==(Graph<NodeType, EdgeType> graph1, Graph<NodeType, EdgeType> graph2)
	{
		/*if (!std::is_same<Type1, Type2>::value)
			return false;*/

		if (graph1.values != graph2.values)
			return false;

		if (graph1.neighbours != graph2.neighbours)
			return false;

		return true;
	}

}


#endif