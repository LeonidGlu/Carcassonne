#pragma once
#include "graph/Graph.h"
#include "graph/UnionFind.h"
#include <unordered_map>

struct RegionInfo {
	int openEdges = 0;
	int tileCount = 0;
};

class TypedRegion {
public:
	int addElement();
	void unite(int idA, int idB);

	bool isClosed(int segmentID) const;
	int getTileCount(int segmentID) const;
	int getOpenEdges(int segmentID) const;
	int getRoot(int segmentID) const;

	void addOpenEdges(int segmentID);
	void removeOpenEdges(int segmentID);
	void incrementTileCount(int segmentID);

	void debug(const std::string& name = "") const;

private:
	UnionFind uf;
	Graph graph;
	std::unordered_map<int, RegionInfo> regions;
};