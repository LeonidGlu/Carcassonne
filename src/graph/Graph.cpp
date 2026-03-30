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

void Graph::debug() const {
	if (adjacencyGraph.empty()) {
		std::cout << "  (empty)\n";
		return;
	}

	for (auto& i : adjacencyGraph) {
		std::cout << "  " << i.first << " -> [";
		for (size_t j = 0; j < i.second.size(); ++j) {
			if (j > 0) std::cout << ", ";
			std::cout << i.second[j];
		}
		std::cout << "]\n";
	}
}