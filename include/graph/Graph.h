#pragma once
#include <unordered_map>
#include <vector>
#include <iostream>

class Graph {
public:
	void addNode(int id);
	void addEdge(int a, int b);

	const std::vector<int>& getNeighbors(int node) const;

	bool hasNode(int id) const;

	void debug() const;

private:
	std::unordered_map<int, std::vector<int>> adjacencyGraph;
};