#pragma once
#include "ai/IEvaluator.h"
#include "ai/GameStateSnapshot.h"

class HeuristicEvaulator : public IEvaluator {
public:
	MoveEvalution evalute(const GameStateSnapshot& snapshot, const Tile& tile, const Move& move, int playerIndex) override;
	std::string getName() const override;

private:
	float evaluteCityValue(const RegionManager& regions, int segmentID, int playerIndex) const;
	float evaluteRoadValue(const RegionManager& regions, int segmentID, int playerIndex) const;
	float evaluteFieldValue(const RegionManager& regions, int segmentID, int playerIndex) const;
	float evaluteMonasteryValue(const RegionManager& regions, Position pos, int playerIndex, const Board& board) const;

};