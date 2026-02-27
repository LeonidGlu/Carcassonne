#pragma once
#include <unordered_map>
#include <vector>

class Graph {
public:
	void addNode(int id);
	void addEdge(int a, int b);

	const std::vector<int>& getNeighbors(int node) const;

	bool hasNode(int id) const;

private:
	std::unordered_map<int, std::vector<int>> adjacencyGraph;
};