#include "kruskalGenerator.hpp"

namespace Generator
{
	void KruskalGenerator::Generate(Data::MazeData& mazeData)
	{
		Math::Graph::Graph<int, Geometry::Edge> graph = mazeData.getGraph();
		Math::Graph::Graph<int, Geometry::Edge> newGraph;
		std::map<int, int> groups;
		std::unordered_map<Math::Graph::Edge, std::optional<Geometry::Edge>> edgeValues = mazeData.getGraph().getEdgesWithValues();

		int groupId = 0;
		for (const auto& [node, value] : mazeData.getGraph().getNodes())
		{
			newGraph.addNode(value);
			groups[value] = groupId;

			++groupId;
		}

		std::vector<std::pair<Math::Graph::Node, Math::Graph::Node>> randomOrderedEdges;

		for (const auto& [from, toVector] : mazeData.getGraph().getEdges())
		{
			for (const Math::Graph::Node& to : toVector)
			{
				randomOrderedEdges.push_back({ from, to });
			}
		}

		Random::Shuffle(randomOrderedEdges);


		for (const auto& [from, to] : randomOrderedEdges)
		{
			if (groups[from.id] != groups[to.id])
			{
				Geometry::Edge wall = *edgeValues[Math::Graph::Edge{ from, to }];
				newGraph.addEdge(from.id, to.id, wall);
				//groups[to.id] = groups[from.id];
				for (auto& [id, group] : groups)
				{
					if (group == groups[to.id])
						group = groups[from.id];
				}
			}
		}

		/*for (const auto& [from, toVector] : edges)
		{
			for (const Math::Graph::Node& to : toVector)
			{
				if (groups[from.id] != groups[to.id])
				{
					newGraph.addEdge(from.id, to.id, edgeValues[Math::Graph::Edge{ from, to }]);
					groups[to.id] = groups[from.id];
				}
			}
		}*/

		mazeData.setMaze(newGraph);
	}
}