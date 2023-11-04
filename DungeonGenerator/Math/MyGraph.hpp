#pragma once

#include <memory>
#include <vector>

namespace Math
{
	template<class Type>
	class Node;

	template<class Type>
	using NodeRef = std::shared_ptr<Node<Type>>;

	/*template<class Type>
	auto CreateNodeRef = std::make_shared<Node<Type>>(int, Type);*/


	template<class Type>
	class Edge;

	template<class Type>
	using EdgeRef = std::shared_ptr<Edge<Type>>;



	template<class Type>
	class Node final
	{
	private:
		int						id;
		std::shared_ptr<Type>	value;

		std::vector<std::shared_ptr<Node<Type>>> neighbours;

	public:
		Node(int id, std::shared_ptr<Type> value) : id{ id }, value{ value } {}

		Type getValue() const
		{
			return *value;
		}

		//void addNeighbour() {}
	};


	template<class Type>
	class Edge final
	{
	private:
		int		id;
		float	weight;

		std::shared_ptr<Node<Type>>	from;
		std::shared_ptr<Node<Type>>	to;

	public:
		Edge(int id, std::shared_ptr<Node<Type>> from, std::shared_ptr<Node<Type>> to, float weight = 1.0f) : id{ id }, weight{ weight }
		{
			this->from = from;
			this->to = to;
		}

		int		getId()		const { return id; }
		float	getWeight() const { return weight; }
	};


	template<class Type>
	class Graph final
	{
	private:
		int nodeCount;
		int edgeCount;

		std::vector <EdgeRef<Type>> edges;
		std::vector <NodeRef<Type>> nodes;


	public:
		Graph()
		{
			nodeCount = 0;
			edgeCount = 0;
		}

		void addNode(Type item);
		void addEdge(Type from, Type to, bool directional = false);


		NodeRef<Type> getNode(Type value)
		{
			for (NodeRef<Type> node : nodes)
				if (node->getValue() == value)
					return node;
			return nullptr;
		}



		std::vector <NodeRef<Type>> getNeighbours(Type item) const;
		std::vector <EdgeRef<Type>> getEdges(Type item) const;
	};

	template<class Type>
	inline void Graph<Type>::addNode(Type item)
	{
		std::shared_ptr<Type> newItem = std::make_shared<Type>(item);
		Node<Type> newNode(nodeCount, newItem);
		NodeRef<Type> newNodeRef = std::make_shared<Node<Type>>(newNode);
		nodes.push_back(newNodeRef);
		++nodeCount;
	}

	template<class Type>
	inline void Graph<Type>::addEdge(Type from, Type to, bool directional)
	{

		Edge<Type> newEdge(edgeCount, this->getNode(from), this->getNode(to));
		EdgeRef<Type> newEdgeRef = std::make_shared<Edge<Type>>(newEdge);

		edges.push_back(newEdgeRef);
		++edgeCount;
	}

	template<class Type>
	inline std::vector<NodeRef<Type>> Graph<Type>::getNeighbours(Type item) const
	{
		std::vector<NodeRef<Type>> result;
		return result;
	}

	template<class Type>
	inline std::vector<EdgeRef<Type>> Graph<Type>::getEdges(Type item) const
	{
		return edges;
	}

}