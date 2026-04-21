#include "core/ScoreCalculator.h"

ScoreCalculator::ScoreCalculator(const RegionManager& regionManager, const Board& board) 
	: regionManager(regionManager), board(board) {}

ScoreResult ScoreCalculator::calcCityScore(int segmentID) const {
	const TypedRegion& region = regionManager.getRegion(TileType::City);

	bool closed = region.isClosed(segmentID);
	int tileCount = region.getTileCount(segmentID);

	int score = closed ? tileCount * 2 : tileCount;
	return ScoreResult{ score, closed };
}

ScoreResult ScoreCalculator::calcRoadScore(int segmentID) const {
	const TypedRegion& region = regionManager.getRegion(TileType::Road);

	bool closed = region.isClosed(segmentID);
	int tileCount = region.getTileCount(segmentID);

	int score = tileCount;
	return ScoreResult{ score, closed };
}

ScoreResult ScoreCalculator::calcMonasteryScore(Position pos) const {
	bool closed = regionManager.isMonasteryClosed(pos, board);
	int score = 1;

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0) {
				continue;
			}
			if (board.hasTile({ pos.x + x, pos.y + y })) {
				score++;
			}
		}
	}
	return ScoreResult{ score, closed };
}