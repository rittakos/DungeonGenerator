#include "kruskalGenerator.hpp"

namespace Generator
{
	void KruskalGenerator::Generate(Data::MazeData& mazeData)
	{
		Math::Graph<int, Geometry::Edge> graph = mazeData.getGraph();
		Math::Graph<int, Geometry::Edge> newGraph;
		std::map<int, int> groups;
		std::unordered_map<Math::Edge, std::optional<Geometry::Edge>> edgeValues = mazeData.getGraph().getEdgesWithValues();

		int groupId = 0;
		for (const auto& [node, value] : mazeData.getGraph().getNodes())
		{
			newGraph.addNode(value);
			groups[value] = groupId;

			++groupId;
		}


		for (const auto& [from, toVector] : mazeData.getGraph().getEdges())
		{
			for (const Math::Node& to : toVector)
			{
				if (groups[from.id] != groups[to.id])
				{
					newGraph.addEdge(from.id, to.id, edgeValues[Math::Edge{ from, to }]);
					groups[to.id] = groups[from.id];
				}
			}
		}

		mazeData.setMaze(newGraph);
	}
}