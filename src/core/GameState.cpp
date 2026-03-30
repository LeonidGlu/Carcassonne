#include "core/GameState.h"

GameState::GameState() : moveGenerator(validator), scoreCalc(regionManager, board) {}

bool GameState::placeTile(Tile tile, Position pos, int& score) {
	score = 0;
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

	score = scoreCalc.calcScore(pos);

	DEBUG_LOG("Score after placed: " << score);

	return true;
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