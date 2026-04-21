#include "core/GameState.h"

GameState::GameState() : moveGenerator(validator), scoreCalc(regionManager, board) {}

bool GameState::placeTile(Tile tile, Position pos) {
	if (!validator.canPlace(tile, pos, board)) {
		DEBUG_LOG("Can't place tile on (" << pos.x << ", " << pos.y << ")");
		return false;
	}

	DEBUG_LOG("Place tile on (" << pos.x << ", " << pos.y << "):");
	DEBUG_CALL(tile.debug());

	regionManager.onTilePlaced(tile, pos, board);
	board.setTile(pos, tile);

	DEBUG_LOG("After placed:");
	DEBUG_CALL(regionManager.debug());

	return true;
}

void GameState::placeMeeple(const Segment& seg, Position pos, int playerIndex) {
	Meeple meeple(playerIndex, tileTypeToMeepleType(seg.type));

	if (seg.type == TileType::Monastery) {
		regionManager.onMonasteryMeeplePlaced(pos, meeple);
	}
	else {
		regionManager.onMeeplePlaced(seg.id, seg.type, meeple);
	}
}

std::vector<Segment> GameState::getAvailableRegions(const Tile& tile) const {
	std::vector<Segment> result;
	std::set<int> visitedRoots;

	for (const Segment& seg : tile.getSegments()) {
		if (seg.type == TileType::Crossroad) {
			continue;
		}
		if (seg.id < 0) {
			if (seg.type == TileType::Monastery) {
				result.push_back(seg);
			}
			continue;
		}

		int root = regionManager.getRegion(seg.type).getRoot(seg.id);
		if (!visitedRoots.count(root)) {
			visitedRoots.insert(root);
			result.push_back(seg);
		}
		
	}
	return result;
}

std::vector<ClosedRegion> GameState::checkAndCloseRegions(Position pos) {
	std::vector<ClosedRegion> closed;
	const Tile& placedTile = board.getTile(pos);
	std::set<std::pair<TileType, int>> processed;

	for (const Segment& seg : placedTile.getSegments()) {
		if (seg.type == TileType::Field) {
			continue;
		}
		if (seg.type == TileType::Crossroad) {
			continue;
		}

		if (seg.type == TileType::Monastery) {
			ScoreResult result = scoreCalc.calcMonasteryScore(pos);
			if (result.isClosed) {
				closed.push_back({ result.score, regionManager.getMonasteryMeeples(pos) });
				regionManager.clearMonasteryMeeples(pos);
			}
			continue;
		}

		int root = regionManager.getRegion(seg.type).getRoot(seg.id);
		auto key = std::make_pair(seg.type, root);

		if (processed.count(key)) {
			continue;
		}
		processed.insert(key);

		ScoreResult result;
		if (seg.type == TileType::City) {
			result = scoreCalc.calcCityScore(seg.id);
		}
		else if (seg.type == TileType::Road) {
			result = scoreCalc.calcRoadScore(seg.id);
		}

		if (result.isClosed) {
			closed.push_back({ result.score, regionManager.getMeeples(seg.id, seg.type) });
			regionManager.clearMeeples(seg.id, seg.type);
		}
	}

	DEBUG_LOG("Score after placed: " << closed.size());

	return closed;
}

std::vector<Move> GameState::getValidMoves(const Tile& tile) const {
	return moveGenerator.generateMoves(tile, board);
}

std::vector<Move> GameState::getValidPositions(const Tile& tile) const {
	return moveGenerator.generatePosition(tile, board);
}

const Board& GameState::getBoard() const {
	return board;
}

const RegionManager& GameState::getRegionManager() const {
	return regionManager;
}

const ScoreCalculator& GameState::getScoreCalc() const {
	return scoreCalc;
}