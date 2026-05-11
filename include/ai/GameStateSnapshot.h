#pragma once
#include "core/GameState.h"
#include "ai/IEvaluator.h"
#include <memory>
#include <unordered_map>

class GameStateSnapshot {
public:
	explicit GameStateSnapshot(const GameState& state);
	~GameStateSnapshot() = default;

	GameStateSnapshot(const GameStateSnapshot&) = delete;
	GameStateSnapshot& operator=(const GameStateSnapshot&) = delete;

	GameStateSnapshot(GameStateSnapshot&&) noexcept = default;
	GameStateSnapshot& operator=(GameStateSnapshot&&) noexcept = default;

	MoveEvalution evalute(const Tile& tile, const Move& move, int playerIndex) const;
	const std::vector<Move>& getValidMoves(const Tile& tile);
	std::vector<Segment> getAvailableRegions(const Tile& tile, Position pos) const;
	void setEvaluator(std::unique_ptr<IEvaluator> eval);

	const Board& getBoard() const;
	const RegionManager& getRegion() const;
	const ScoreCalculator& getScoreCalculator() const;
	const PlacementValidator& getValidator() const;

	bool isMoveLegal(const Tile& tile, const Move& move) const;
	int calculateImmediateScore(const Tile& tile, const Move& move) const;

private:
	const Board& board;
	const PlacementValidator& validator;
	RegionManager regionManager;
	ScoreCalculator scoreCalculator;
	std::unique_ptr<IEvaluator> evaluator;

	mutable std::unordered_map<size_t, std::vector<Move>> movesCache;
	mutable std::unordered_map<size_t, std::vector<Segment>> regionsCache;

	size_t hashTile(const Tile& tile) const;
	size_t hashPosition(Position pos) const;


};