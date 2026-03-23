#include "Board.h"
#include "core/RegionManager.h"
#include "core/PlacementValidator.h"
#include "core/MoveGenerator.h"
#include "core/ScoreCalculator.h"
#include "common/Position.h"
#include "tiles/Tile.h"
#include <vector>

class GameState {
public:
	GameState();

	bool placeTile(Tile tile, Position pos, int& score);
	
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

};
