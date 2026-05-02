#pragma once
#include "meeple/Meeple.h"
#include "core/Board.h"
#include "core/RegionManager.h"
#include "core/PlacementValidator.h"
#include "core/MoveGenerator.h"
#include "core/ScoreCalculator.h"
#include "common/Position.h"
#include "common/Debug.h"
#include "tiles/Tile.h"
#include <vector>

struct ClosedRegion {
	int score = 0;
	std::vector<Meeple> meeples;
};

class GameState {
public:
	GameState();

	bool placeTile(Tile tile, Position pos);
	void placeMeeple(const Segment& seg, Position pos, int playerIndex);
	std::vector<ClosedRegion> checkAndCloseRegions(Position pos);

	std::vector<Segment> getAvailableRegions(const Tile& tile) const;
	std::vector<Move> getValidMoves(const Tile& tile) const;
	std::vector<Move> getValidPositions(const Tile& tile) const;

	const Board& getBoard() const;
	const RegionManager& getRegionManager() const;
	const ScoreCalculator& getScoreCalc() const;

private:
	Board board;
	RegionManager regionManager;
	PlacementValidator validator;
	MoveGenerator moveGenerator;
	ScoreCalculator scoreCalc;

	void checkNeighborsMonasteries(Position pos, std::vector<ClosedRegion>& closed);

};
