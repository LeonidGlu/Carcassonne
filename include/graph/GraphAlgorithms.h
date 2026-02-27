#pragma once
#include "Graph.h"
#include <vector>

class GraphAlgorithms {
public:
	static std::vector<int> bfs(const Graph& graph, int start);
};