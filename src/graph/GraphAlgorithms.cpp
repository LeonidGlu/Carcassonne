#include "graph/GraphAlgorithms.h"
#include <queue>
#include <unordered_set>

std::vector<int> GraphAlgorithms::bfs(const Graph& graph, int start) {
	std::vector<int> component;

	if (!graph.hasNode(start)) return component;

	std::queue<int> q;
	std::unordered_set<int> visited;

	q.push(start);
	visited.insert(start);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		component.push_back(current);
		for (int neighbor : graph.getNeighbors(current)) {
			if (!visited.count(neighbor)) {
				visited.insert(neighbor);
				q.push(neighbor);
			}
		}
	}
	
	return component;
}