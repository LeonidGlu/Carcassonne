#pragma once
#include "Board.h"
#include "tiles/Tile.h"
#include "TypedRegion.h"
#include <set>
#include <array>

class RegionManager {
public:
	void onTilePlaced(Tile& tile, Position pos, const Board& board);

	void onMeeplePlaced(int segmentID, TileType type, Meeple meeple);
	void onMonasteryMeeplePlaced(Position pos, Meeple meeple);

	std::vector<Meeple> getMeeples(int segmentID, TileType type) const;
	std::vector<Meeple> getMonasteryMeeples(Position pos) const;

	void clearMeeples(int segmentID, TileType type);
	void clearMonasteryMeeples(Position pos);

	bool isMonasteryClosed(Position pos, const Board& board) const;
	
	TypedRegion& getRegion(TileType type);
	const TypedRegion& getRegion(TileType type) const;

	void debug() const;

private:
	TypedRegion cityRegion;
	TypedRegion roadRegion;
	TypedRegion fieldRegion;

	std::map<Position, std::vector<Meeple>> monasteryMeeples;

	void initializeSegments(Tile& tile);
	void connectWithNeighbors(Tile& tile, Position pos, const Board& board);
	void updateRegionInfo(Tile& tile, Position pos, const Board& board);
};