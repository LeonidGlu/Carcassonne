#pragma once
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <iostream>

class Graph {
public:
	void addNode(int id);
	void addEdge(int a, int b);
	void removeNode(int id);
	void clear();

	const std::vector<int>& getNeighbors(int node) const;
	const std::unordered_map<int, std::vector<int>> getAdjacencyGraph() const;

	bool isEmpty() const;

	bool hasNode(int id) const;

	void debug() const;

private:
	std::unordered_map<int, std::vector<int>> adjacencyGraph;
};