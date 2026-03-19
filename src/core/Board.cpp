#include "core/Board.h"

const Tile& Board::getTile(Position pos) const {
	return tiles.at(pos);
}

Tile& Board::getTile(Position pos) {
	return tiles.at(pos);
}

const std::map<Position, Tile>& Board::getAllTiles() const {
	return tiles;
}

bool Board::hasTile(Position pos) const {
	return tiles.count(pos) > 0;
}

void Board::setTile(Position pos, Tile tile) {
	tiles[pos] = std::move(tile);
}

bool Board::isEmpty() const {
	return tiles.empty();
}
