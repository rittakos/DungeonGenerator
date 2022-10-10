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
		Node(int id, std::shared_ptr<Type> value);

		void addNeighbour();
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
		Edge(int id, std::shared_ptr<Node<Type>> from, std::shared_ptr<Node<Type>> to, int weight = 1);

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

		

		std::vector <NodeRef<Type>> getNeighbours(Type item) const;
		std::vector <EdgeRef<Type>> getEdges(Type item) const;
	};

	template<class Type>
	inline void Graph<Type>::addNode(Type item)
	{
		/*NodeRef<Type> newNode = std::make_shared<Node<Type>>(nodeCount, item);
		nodes.push_back(newNode);
		++nodeCount;*/
	}

	template<class Type>
	inline void Graph<Type>::addEdge(Type from, Type to, bool directional)
	{
		//EdgeRef<Type> newEdge = std::make_shared<Edge<Type>>(ed)
	}

	template<class Type>
	inline std::vector<NodeRef<Type>> Graph<Type>::getNeighbours(Type item) const
	{
		return std::vector<Type>();
	}

	template<class Type>
	inline std::vector<EdgeRef<Type>> Graph<Type>::getEdges(Type item) const
	{
		return edges;
	}

}