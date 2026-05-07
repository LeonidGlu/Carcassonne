#include "graph/Graph.h"

void Graph::addNode(int id) {
	if (!hasNode(id)) {
		adjacencyGraph[id] = std::vector<int>();
	}
}

void Graph::addEdge(int a, int b) {
	addNode(a);
	addNode(b);

	auto& neighborsA = adjacencyGraph[a];
	if (std::find(neighborsA.begin(), neighborsA.end(), b) == neighborsA.end()) {
		neighborsA.push_back(b);
	}

	auto& neighborsB = adjacencyGraph[b];
	if (std::find(neighborsB.begin(), neighborsB.end(), a) == neighborsB.end()) {
		neighborsB.push_back(a);
	}
}

void Graph::removeNode(int id) {
	if (!hasNode(id)) {
		return;
	}

	for (int neighbor : adjacencyGraph[id]) {
		auto& neighbors = adjacencyGraph[neighbor];
		neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), id), neighbors.end());
	}
	adjacencyGraph.erase(id);
}

void Graph::clear() {
	adjacencyGraph.clear();
}

const std::vector<int>& Graph::getNeighbors(int node) const {
	static const std::vector<int> empty;
	auto it = adjacencyGraph.find(node);
	if (it == adjacencyGraph.end()) {
		return empty;
	}
	return it->second;
}

const std::unordered_map<int, std::vector<int>> Graph::getAdjacencyGraph() const {
	return adjacencyGraph;
}

bool Graph::isEmpty() const {
	return adjacencyGraph.empty();
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