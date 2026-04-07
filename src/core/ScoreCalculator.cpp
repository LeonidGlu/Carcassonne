#include "core/ScoreCalculator.h"

ScoreCalculator::ScoreCalculator(const RegionManager& regionManager, const Board& board) 
	: regionManager(regionManager), board(board) {}

int ScoreCalculator::calcScore(Position pos) const {
	const Tile& tile = board.getTile(pos);
	int totalScore = 0;

	std::set<std::pair<TileType, int>> scoredRoots;

	for (const Segment& seg : tile.getSegments()) {
		if (seg.type == TileType::Field) {
			continue;
		}
		if (seg.type == TileType::Crossroad) {
			continue;
		}
		if (seg.type == TileType::Monastery) {
			ScoreResult result = calcMonasteryScore(pos);
			if (result.isClosed) {
				totalScore += result.score;
			}
			continue;
		}

		int root = regionManager.getRegion(seg.type).getRoot(seg.id);
		auto key = std::make_pair(seg.type, root);


		if (scoredRoots.count(key)) {
			continue;
		}
		scoredRoots.insert(key);
		ScoreResult result;

		if (seg.type == TileType::City) {
			result = calcCityScore(seg.id);
		}
		else if (seg.type == TileType::Road) {
			result = calcRoadScore(seg.id);
		}

		if (result.isClosed) {
			totalScore += result.score;
		}
	}

	return totalScore;
}

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