#pragma once
#include "Board.h"

class PlacementValidator {
public:
	bool canPlace(const Tile& tile, Position pos, const Board& board) const;

private:
	bool hasNeighbor(Position pos, const Board& board) const;
	bool edgesMatch(const Tile& tile, Position pos, const Board& board) const;
};