#pragma once
#include "Board.h"
#include "PlacementValidator.h"
#include <vector>
#include <set>

struct Move {
	Position pos;
	int rotation;
};

class MoveGenerator {
public:
	MoveGenerator(const PlacementValidator& validator);

	std::vector<Move> generateMoves(const Tile& tile, const Board& board) const;
	std::vector<Move> generatePosition(const Tile& tile, const Board& board) const;

private:
	const PlacementValidator& validator;

	std::vector<Position> getEmptyNeighbors(const Board& board) const;
};