#include "graph/Graph.h"

void Graph::addNode(int id) {
	if (!hasNode(id)) {
		adjacencyGraph[id] = std::vector<int>();
	}
}

void Graph::addEdge(int a, int b) {
	addNode(a);
	addNode(b);

	adjacencyGraph[a].push_back(b);
	adjacencyGraph[b].push_back(a);
}

const std::vector<int>& Graph::getNeighbors(int node) const {
	static const std::vector<int> empty;
	auto it = adjacencyGraph.find(node);
	if (it == adjacencyGraph.end()) {
		return empty;
	}
	return it->second;
}

bool Graph::hasNode(int id) const {
	return adjacencyGraph.find(id) != adjacencyGraph.end();
}