#include "ai/GameStateSnapshot.h"
#include "ai/HeuristicEvaulator.h"

 GameStateSnapshot::GameStateSnapshot(const GameState& state) 
	 : board(state.getBoard()), 
	 validator(state.getValidator()),
	 regionManager(state.getRegionManager()),
	 scoreCalculator(regionManager, board),
	 evaluator(std::make_unique<HeuristicEvaulator>()) 
 {}

 void GameStateSnapshot::setEvaluator(std::unique_ptr<IEvaluator> eval) {
	 evaluator = std::move(eval);
 }

 MoveEvalution GameStateSnapshot::evalute(const Tile& tile, const Move& move, int playerIndex) const {
	 if (!evaluator) {
		 MoveEvalution eval;
		 eval.isLegal = isMoveLegal(tile, move);
		 return eval;
	 }

	 return evaluator->evalute(*this, tile, move, playerIndex);
 }

 bool GameStateSnapshot::isMoveLegal(const Tile& tile, const Move& move) const {
	 Tile rotatedTile = tile;
	 for (int i = 0; i < move.rotation; ++i) {
		 rotatedTile.rotate();
	 }

	 return validator.canPlace(rotatedTile, move.pos, board);
 }

 int GameStateSnapshot::calculateImmediateScore(const Tile& tile, const Move& move) const {
	 Tile rotatedTile = tile;
	 for (int i = 0; i < move.rotation; ++i) {
		 rotatedTile.rotate();
	 }

	 RegionManager testRegions = regionManager;
	 Tile mutableTile = rotatedTile;
	 testRegions.onTilePlaced(mutableTile, move.pos, board);

	 int score = 0;

	 for (const Segment& seg : mutableTile.getSegments()) {
		 if (seg.type == TileType::City) {
			 if (testRegions.getRegion(TileType::City).isClosed(seg.id)) {
				 score += scoreCalculator.calcCityScore(seg.id).score;
			 }
		 }
		 else if (seg.type == TileType::Road) {
			 if (testRegions.getRegion(TileType::Road).isClosed(seg.id)) {
				 score += scoreCalculator.calcRoadScore(seg.id).score;
			 }
		 }
		 else if (seg.type == TileType::Monastery) {
			 if (testRegions.isMonasteryClosed(move.pos, board)) {
				 score += scoreCalculator.calcMonasteryScore(move.pos).score;
			 }
		 }
	 }

	 return score;
 }

 const std::vector<Move>& GameStateSnapshot::getValidMoves(const Tile& tile) {
	 size_t hash = hashTile(tile);

	 auto it = movesCache.find(hash);
	 if (it != movesCache.end()) {
		 return it->second;
	 }

	 MoveGenerator moveGenerator(validator);
	 auto& moves = movesCache[hash];
	 moves = moveGenerator.generateMoves(tile, board);
	 return moves;
 }

 std::vector<Segment> GameStateSnapshot::getAvailableRegions(const Tile& tile, Position pos) const {
	 size_t hash = hashTile(tile) ^ (hashPosition(pos) << 16);
	 auto it = regionsCache.find(hash);
	 if (it != regionsCache.end()) {
		 return it->second;
	 }

	 std::vector<Segment> result;
	 std::set<std::pair<TileType, int>> visitedRoots;

	 RegionManager tempRegions = regionManager;
	 Tile tempTile = tile;
	 tempRegions.onTilePlaced(tempTile, pos, board);

	 for (const Segment& seg : tempTile.getSegments()) {
		 if (seg.type == TileType::Crossroad) {
			 continue;
		 }

		 if (seg.id < 0) {
			 continue;
		 }

		 if (seg.type == TileType::Monastery) {
			 if (tempRegions.getMonasteryMeeples(pos).empty()){
				 result.push_back(seg);
			 }
			 continue;
		 }

		 int root = tempRegions.getRegion(seg.type).getRoot(seg.id);
		 auto key = std::make_pair(seg.type, root);

		 if (visitedRoots.count(key)) {
			 continue;
		 }

		 visitedRoots.insert(key);

		 if (tempRegions.getRegion(seg.type).getMeeples(seg.id).empty()) {
			 result.push_back(seg);
		 }
	 }

	 regionsCache[hash] = result;
	 return result;
 }

 size_t GameStateSnapshot::hashTile(const Tile& tile) const {
	 size_t hash = 0;
	 for (const auto& seg : tile.getSegments()) {
		 hash = hash * 31 + static_cast<size_t>(seg.type);
	 }

	 for (int i = 0; i < 9; ++i) {
		 hash = hash * 31 + static_cast<size_t>(tile.getSegmentIndex(static_cast<TilePosition>(i)));
	 }

	 return hash;
 }

 size_t GameStateSnapshot::hashPosition(Position pos) const {
	 return static_cast<size_t>(pos.x * 10000 + pos.y);
 }

 const Board& GameStateSnapshot::getBoard() const {
	 return board;
 }

 const RegionManager& GameStateSnapshot::getRegion() const {
	 return regionManager;
 }

 const ScoreCalculator& GameStateSnapshot::getScoreCalculator() const {
	 return scoreCalculator;
 }

 const PlacementValidator& GameStateSnapshot::getValidator() const {
	 return validator;
 }