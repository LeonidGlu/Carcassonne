#pragma once
#include "core/MoveGenerator.h"

struct MoveEvalution {
	Move move;
	float score = -9999.0f;
	float immediateReward = 0.0f;
	float potentialReward = 0.0f;
	bool isLegal = false;
};

class IEvaluator {
public:

	virtual ~IEvaluator() = default;
	virtual MoveEvalution evalute(const class GameStateSnapshot& snapshot, const Tile& tile, const Move& move, int playerIndex) = 0;
	virtual std::string getName() const = 0;
};