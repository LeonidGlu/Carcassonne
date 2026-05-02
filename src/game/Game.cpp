#include "game/Game.h"

Game::Game(int playerCount) {
	if (playerCount < 2 || playerCount > 5) {
		throw std::invalid_argument("The number of players should be between 2 and 5!");
	}

	for (int i = 0; i < playerCount; ++i) {
		std::cout << "Enter the player's name " << (i + 1) << ": ";
		std::string name;
		std::cin >> name;
		players.emplace_back(name);
	}
}

void Game::run() {
	placeStartTile();

	while (!deck.isEmpty()) {
		playTurn();
		nextPlayer();
	}

	endGame();
}

void Game::placeStartTile() {
	Tile startTile = TileFactory::create("StartTile");

	std::vector<ClosedRegion> closedRegion;
	gameState.placeTile(startTile, { 0, 0 });
	render.renderBoard(gameState.getBoard());
}

void Game::playTurn() {
	Player& player = currentPlayerRef();

	renderCurrentBoard(players);

	std::cout << "--------------------------\n";
	std::cout << player.getName() << "'s turn\n";
	std::cout << "There are still tiles left in the deck: " << deck.remaining() << "\n";
	std::cout << "--------------------------\n";

	Tile tile = deck.draw();
	render.renderTile(tile);
	

	Move move = getPlayerMove(tile);

	for (int i = 0; i < move.rotation; ++i) {
		tile.rotate();
	}

	if (!gameState.placeTile(tile, move.pos)) {
		std::cout << "Errror! Can't place tile!\n";
		return;
	}

	handleMeeple(gameState.getBoard().getTile(move.pos), move.pos);

	std::vector<ClosedRegion> closed = gameState.checkAndCloseRegions(move.pos);

	processClosedRegions(closed);

	renderCurrentBoard(players);
}

void Game::nextPlayer() {
	currentPlayer = (currentPlayer + 1) % static_cast<int>(players.size());
}

void Game::endGame() {
	std::cout << "--------------------------\n";
	std::cout << "GAME OVER\n";
	std::cout << "--------------------------\n";

	renderCurrentBoard(players);

	int maxScore = -1;
	std::vector<std::string> winners;
	for (const auto& player : players) {
		if (player.getScore() > maxScore) {
			maxScore = player.getScore();
			winners.clear();
			winners.push_back(player.getName());
		}
		else if (maxScore == player.getScore()) {
			winners.push_back(player.getName());
		}
	}

	if (winners.size() == 1) {
		std::cout << "\nWinner: " << winners[0] << " with " << maxScore << " points\n";
	}
	else {
		std::cout << "\nA draw between: ";
		for (size_t i = 0; i < winners.size(); ++i) {
			std::cout << winners[i] << " ";
		}
		std::cout << "with " << maxScore << " points\n";
	}
}

Move Game::getPlayerMove(const Tile& tile) {
	while (true) {
		int rotation = askRotation();

		Tile rotatedTile = tile;
		for (int i = 0; i < rotation; ++i) {
			rotatedTile.rotate();
		}

		std::vector<Move> moves = gameState.getValidPositions(rotatedTile);

		if (moves.empty()) {
			std::cout << "There are no acceptable moves for such a tile rotation\n" << "Try another rotation\n";
			continue;
		}

		//render.clearScreen();
		render.renderBoardWithMoves(gameState.getBoard(), moves);
		render.renderTile(rotatedTile);

		Move selected = askPosition(moves);
		selected.rotation = rotation;

		return selected;
	}
}

int Game::askRotation() const {
	std::cout << "Choose a rotation:\n"
		<< "0 - no rotation\n"
		<< "1 - 90 degree rotation\n"
		<< "2 - 180 degree rotation\n"
		<< "3 - 270 degree rotation\n"
		<< "Your choose: ";

	int rotation;
	while (true) {
		if (std::cin >> rotation && rotation >= 0 && rotation <= 3) {
			break;
		}
		std::cout << "Incorrect input\nEnter 0, 1, 2 or 3: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return rotation;
}

Move Game::askPosition(const std::vector<Move>& moves) const {
	std::cout << "\nSelect the move number (0-" << moves.size() - 1 << "): ";

	int choose;
	while (true) {
		if (std::cin >> choose && choose >= 0 && choose < static_cast<int>(moves.size())) {
			break;
		}
		std::cout << "Incorrect input\nEnter a number from 0 to " << moves.size() - 1 << ": ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return moves[choose];
}

void Game::processClosedRegions(const std::vector<ClosedRegion>& closedRegions) {
	for (const ClosedRegion& region : closedRegions) {
		if (region.meeples.empty()) {
			continue;
		}
		std::unordered_map<int, int> meepleCount;
		for (const Meeple& meeple : region.meeples) {
			meepleCount[meeple.getPlayer()]++;
		}

		int maxCount = 0;
		for (auto& i : meepleCount) {
			maxCount = std::max(maxCount, i.second);
		}

		for (auto& i : meepleCount) {
			if (i.second == maxCount) {
				players[i.first].addScore(region.score);
				std::cout << players[i.first].getName() << " scored " << region.score << " points!\n";
			}
		}

		for (const Meeple& meeple : region.meeples) {
			players[meeple.getPlayer()].returnMeeple();
		}
	}
}

void Game::handleMeeple(const Tile& tile, Position pos) {
	Player& player = currentPlayerRef();

	if (!player.hasMeeple()) {
		std::cout << "You have no meeples left!\n";
		return;
	}

	std::vector<Segment> regions = gameState.getAvailableRegions(tile);

	if (regions.empty()) {
		std::cout << "No available regions for meeple!\n";
		return;
	}

	std::cout << "\n----- PLACE MEEPLE -----\n";
	std::cout << "Availabble regions:\n";
	for (size_t i = 0; i < regions.size(); ++i) {
		std::cout << "[" << i << "] - " << regions[i].type << "\n";
	}

	std::cout << "[" << regions.size() << "] - Skip\n";

	int choise = askMeeple(regions);

	if (choise == static_cast<int>(regions.size())) {
		std::cout << "Skipped meeple placement!\n";
		return;
	}

	player.placeMeeple();
	gameState.placeMeeple(regions[choise], pos, currentPlayer);
	std::cout << "Meeple placed!\n";
}

int Game::askMeeple(const std::vector<Segment>& regions) const {
	int choose;

	std::cout << "Yout choise (0 - " << regions.size() << "): ";

	while (true) {
		if (std::cin >> choose && choose >= 0 && choose <= static_cast<int>(regions.size())) {
			break;
		}
		std::cout << "Incorrect input\nEnter a number from 0 to " << regions.size() << ": ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return choose;
}

void Game::renderMeepleInfo() const {
	const Board& board = gameState.getBoard();
	const RegionManager& rm = gameState.getRegionManager();

	std::cout << "\n----- MEEPLES -----\n";
	std::set<std::pair<TileType, int>> visited;

	for (const auto& tile : board.getAllTiles()) {
		for (const Segment& seg : tile.second.getSegments()) {
			if (seg.id < 0) {
				continue;
			}
			if (seg.type == TileType::Crossroad) {
				continue;
			}

			int root = rm.getRegion(seg.type).getRoot(seg.id);
			auto key = std::make_pair(seg.type, root);
			if (visited.count(key)) {
				continue;
			}

			visited.insert(key);

			auto meeples = rm.getMeeples(seg.id, seg.type);
			if (meeples.empty()) {
				continue;
			}
			
			render.renderMeepleInfo(seg.type, tile.first, meeples, players);
		}
	}
}

void Game::renderCurrentBoard(const std::vector<Player>& players) const {
	render.clearScreen();
	render.renderBoard(gameState.getBoard());
	renderMeepleInfo();
	render.renderScores(players);
}

Player& Game::currentPlayerRef() {
	return players[currentPlayer];
}