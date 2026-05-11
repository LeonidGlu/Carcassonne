#include "ai/HeuristicEvaulator.h"
#include "ai/GameStateSnapshot.h"

MoveEvalution HeuristicEvaulator::evalute(const GameStateSnapshot& snapshot, const Tile& tile, const Move& move, int playerIndex) {
	MoveEvalution eval;
	eval.move = move;

	if (!snapshot.isMoveLegal(tile, move)) {
		eval.isLegal = false;
		eval.score = -10000.0f;
		return eval;
	}
	eval.isLegal = true;

	Tile rotatedTile = tile;
	for (int i = 0; i < move.rotation; ++i) {
		rotatedTile.rotate();
	}

	eval.immediateReward = static_cast<float>(snapshot.calculateImmediateScore(tile, move));

	RegionManager testRegions = snapshot.getRegion();
	Tile mutableTile = rotatedTile;
	testRegions.onTilePlaced(mutableTile, move.pos, snapshot.getBoard());

	float potentialScore = 0;

	for (const Segment& seg : mutableTile.getSegments()) {
		if (seg.type == TileType::City) {
			potentialScore += evaluteCityValue(testRegions, seg.id, playerIndex);
		}
		else if (seg.type == TileType::Road) {
			potentialScore += evaluteRoadValue(testRegions, seg.id, playerIndex);
		}
		else if (seg.type == TileType::Field) {
			potentialScore += evaluteFieldValue(testRegions, seg.id, playerIndex);
		}
		else if (seg.type == TileType::Monastery) {
			potentialScore += evaluteMonasteryValue(testRegions, move.pos, playerIndex, snapshot.getBoard());
		}
	}

	eval.potentialReward = potentialScore;

	float bonus = 0;

	const std::array<Position, 4> neighbors = { {
		{move.pos.x, move.pos.y + 1}, {move.pos.x + 1, move.pos.y},
		{move.pos.x, move.pos.y - 1}, {move.pos.x - 1, move.pos.y}
	} };
	int connections = 0;
	for (const auto& pos : neighbors) {
		if (snapshot.getBoard().hasTile(pos)) {
			connections++;
		}
	}
	bonus += connections * 2.0f;

	auto availableRegions = snapshot.getAvailableRegions(rotatedTile, move.pos);
	if (!availableRegions.empty()) {
		bonus += 5.0f;
	}

	eval.score = eval.immediateReward + eval.potentialReward + bonus;
	return eval;
}

float HeuristicEvaulator::evaluteCityValue(const RegionManager& regions, int segmentID, int playerIndex) const {
	const auto& cityRegion = regions.getRegion(TileType::City);
	int tileCount = cityRegion.getTileCount(segmentID);
	int openEdges = cityRegion.getOpenEdges(segmentID);
	bool closed = cityRegion.isClosed(segmentID);

	if (closed) {
		return 0;
	}

	float value = tileCount * 2.0f;

	if (openEdges <= 2 && tileCount >= 3) {
		value += 10.0f;
	}

	auto meeples = cityRegion.getMeeples(segmentID);
	bool hasMyMeeple = false;
	for (const auto& meeple : meeples) {
		if (meeple.getPlayer() == playerIndex) {
			hasMyMeeple = true;
		}
	}

	if (hasMyMeeple) {
		value += 5.0f;
	}
	else if (meeples.empty()) {
		value += 8.0f;
	}
	else {
		value -= 3.0f;
	}

	return value;
}

float HeuristicEvaulator::evaluteRoadValue(const RegionManager& regions, int segmentID, int playerIndex) const {
	const auto& roadRegion = regions.getRegion(TileType::Road);
	int tileCount = roadRegion.getTileCount(segmentID);
	bool closed = roadRegion.isClosed(segmentID);

	if (closed) {
		return 0;
	}

	float value = tileCount * 1.0f;

	auto meeples = roadRegion.getMeeples(segmentID);
	bool hasMyMeeple = false;
	for (const auto& meeple : meeples) {
		if (meeple.getPlayer() == playerIndex) {
			hasMyMeeple = true;
		}
	}

	if (hasMyMeeple) {
		value += 2.0f;
	}
	else if (meeples.empty()) {
		value += 4.0f;
	}

	return value;
}

float HeuristicEvaulator::evaluteFieldValue(const RegionManager& regions, int segmentID, int playerIndex) const {
	const auto& fieldRegion = regions.getRegion(TileType::Field);
	int fieldRoot = fieldRegion.getRoot(segmentID);
	int encodedField = RegionManager::encodedRegion(TileType::Field, fieldRoot);
	const Graph& regionGraph = regions.getRegionGraph();

	int adjacentGities = 0;
	for (int neighbor : regionGraph.getNeighbors(encodedField)) {
		auto decoded = RegionManager::decodedRegion(neighbor);
		if (decoded.first == TileType::City) {
			if (regions.getRegion(TileType::City).isClosed(decoded.second)) {
				adjacentGities++;
			}
		}
	}

	float value = adjacentGities * 3.0f;

	auto meeples = fieldRegion.getMeeples(segmentID);
	bool hasMyMeeple = false;
	for (const auto& meeple : meeples) {
		if (meeple.getPlayer() == playerIndex) {
			hasMyMeeple = true;
		}
	}

	if (hasMyMeeple) {
		value += 5.0f;
	}
	else if (meeples.empty()) {
		value += 8.0f;
	}

	return value;
}

float HeuristicEvaulator::evaluteMonasteryValue(const RegionManager& regions, Position pos, int playerIndex, const Board& board) const {
	int surroundingTiles = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
			if (dx == 0 && dy == 0) {
				continue;
			}
            if (board.hasTile({pos.x + dx, pos.y + dy})) {
                surroundingTiles++;
            }
        }
    }

	float value = surroundingTiles * 1.0f;

	auto meeples = regions.getMonasteryMeeples(pos);
	bool hasMyMeeple = false;
	for (const auto& meeple : meeples) {
		if (meeple.getPlayer() == playerIndex) {
			hasMyMeeple = true;
		}
	}

	if (hasMyMeeple) {
		value += 3.0f;
	}
	else if (meeples.empty()) {
		value += 6.0f;
	}

	return value;
}

std::string HeuristicEvaulator::getName() const {
	return "HeuristicEvaulator";
}