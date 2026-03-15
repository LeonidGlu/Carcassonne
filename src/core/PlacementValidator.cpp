#include "core/PlacementValidator.h"

bool PlacementValidator::canPlace(const Tile& tile, Position pos, const Board& board) const {
	if (board.isEmpty()) {
		return true;
	}
	if (board.hasTile(pos)) {
		return false;
	}
	if (!hasNeighbor(pos, board)) {
		return false;
	}
	return edgesMatch(tile, pos, board);
}

bool PlacementValidator::hasNeighbor(Position pos, const Board& board) const {
	const std::array<Position, 4> deltas = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} };

	for (auto d : deltas) {
		if (board.hasTile({pos.x + d.x, pos.y + d.y})) {
			return true;
		}
	}
	return false;
}

bool PlacementValidator::edgesMatch(const Tile& tile, Position pos, const Board& board) const {
	const std::array<Position, 4> deltas = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} };

	for (int d = 0; d < 4; ++d) {
		Direction dir = static_cast<Direction>(d);
		Position neighborPos{ pos.x + deltas[d].x, pos.y + deltas[d].y };

		if (!board.hasTile(neighborPos)) {
			continue;
		}

		const Tile& neighbor = board.getTile(neighborPos);

		int segIndex = tile.getSegmentIndex(dir);
		int neighborIndex = neighbor.getSegmentIndex(opposite(dir));

		if (tile.getSegment(segIndex).type != neighbor.getSegment(neighborIndex).type) {
			return false;
		}
	}
	return true;
}