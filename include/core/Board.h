#pragma once
#include <map>
#include "tiles/Tile.h"
#include "common/Position.h"

class Board {
public:
	bool hasTile(Position pos) const;
	
	const Tile& getTile(Position pos) const;
	Tile& getTile(Position pos);
	const std::map<Position, Tile>& getAllTiles() const;

	void setTile(Position pos, Tile tile);

	bool isEmpty() const;

private:
	std::map<Position, Tile> tiles;
};