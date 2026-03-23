#include "core/MoveGenerator.h"

MoveGenerator::MoveGenerator(const PlacementValidator& validator) : validator(validator) {}

std::vector<Move> MoveGenerator::generateMoves(const Tile& tile, const Board& board) const {
	std::vector<Move> moves;
	auto candidates = getEmptyNeighbors(board);

	Tile rotatedTile = tile;

	for (int rotation = 0; rotation < 4; ++rotation) {
		for (Position pos : candidates) {
			if (validator.canPlace(rotatedTile, pos, board)) {
				moves.push_back({ pos, rotation });
			}
		}
		rotatedTile.rotate();
	}
	return moves;
}

std::vector<Move> MoveGenerator::generatePosition(const Tile& tile, const Board& board) const {
	std::vector<Move> moves;
	auto candidates = getEmptyNeighbors(board);

	for (Position pos : candidates) {
		if (validator.canPlace(tile, pos, board)) {
			moves.push_back({ pos, 0 });
		}
	}

	return moves;
}

std::vector<Position> MoveGenerator::getEmptyNeighbors(const Board& board) const {
	const std::array<Position, 4> deltas = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} };
	std::set<Position> candidates;

	for (auto& i : board.getAllTiles()) {
		for (auto& d : deltas) {
			Position neighbor{ i.first.x + d.x, i.first.y + d.y };

			if (!board.hasTile(neighbor)) {
				candidates.insert(neighbor);
			}
		}
	}
	return std::vector<Position>(candidates.begin(), candidates.end());
}