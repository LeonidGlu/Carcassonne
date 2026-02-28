#pragma once
#include <map>
#include "Tile.h"
#include "Position.h"
#include "../graph/Graph.h"
#include "../graph/UnionFind.h"

class Board {
public:
	bool canPlaceTile(const Tile& tile, Position pos) const;
	bool placeTile(Tile tile, Position pos);
	bool isCityClosed(int segmentID);

private:
	std::map<Position, Tile> tiles;

	UnionFind cityUF;
	UnionFind roadUF;
	UnionFind fielUF;

	Graph cityGraph;
	Graph roadGraph;
	Graph fielGraph;
	
	void initializeSegments(Tile& tile);
	void connectSegments(Tile& tile);
	void connectWithNeighbors(Tile& tile, Position pos);
};