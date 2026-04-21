#pragma once
#include "RegionManager.h"
#include "tiles/TileType.h"
#include "common/Position.h"

struct ScoreResult {
    int score = 0;
    bool isClosed = false;
};

class ScoreCalculator {
public:
    ScoreCalculator(const RegionManager& regionManager, const Board& board);

    ScoreResult calcMonasteryScore(Position pos) const;
    ScoreResult calcCityScore(int segmentID) const;
    ScoreResult calcRoadScore(int segmentID) const;

private:
    const RegionManager& regionManager;
    const Board& board;
};