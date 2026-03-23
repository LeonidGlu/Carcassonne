#pragma once
#include "Board.h"
#include "tiles/Tile.h"
#include "TypedRegion.h"
#include <set>
#include <array>

class RegionManager {
public:
	void onTilePlaced(Tile& tile, Position pos, const Board& board);

	bool isMonasteryClosed(Position pos, const Board& board) const;
	
	TypedRegion& getRegion(TileType type);
	const TypedRegion& getRegion(TileType type) const;

private:
	TypedRegion cityRegion;
	TypedRegion roadRegion;
	TypedRegion fieldRegion;

	void initializeSegments(Tile& tile);
	void connectWithNeighbors(Tile& tile, Position pos, const Board& board);
	void updateRegionInfo(Tile& tile, Position pos, const Board& board);
};