#pragma once
#include "Tile.h"
#include "Position.h"
#include "../graph/Graph.h"
#include "../graph/UnionFind.h"
#include <map>

class Board {
public:
	bool placeTile(Tile tile, Position pos);
	bool isCityClosed(int segmentID);
};