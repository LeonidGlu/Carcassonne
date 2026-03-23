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

	int score = 0;
	gameState.placeTile(startTile, { 0, 0 }, score);
	render.renderBoard(gameState.getBoard());
}

void Game::playTurn() {
	Player& player = currentPlayerRef();

	render.clearScreen();
	render.renderBoard(gameState.getBoard());
	render.renderScores(players);

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

	int score = 0;
	if (!gameState.placeTile(tile, move.pos, score)) {
		std::cout << "Errror! Can't place tile!\n";
	}

	if (score > 0) {
		player.addScore(score);
	}

	render.clearScreen();
	render.renderBoard(gameState.getBoard());
	render.renderScores(players);

}

void Game::nextPlayer() {
	currentPlayer = (currentPlayer + 1) % static_cast<int>(players.size());
}

void Game::endGame() {
	std::cout << "--------------------------\n";
	std::cout << "GAME OVER\n";
	std::cout << "--------------------------\n";

	render.renderBoard(gameState.getBoard());
	render.renderScores(players);

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

		render.clearScreen();
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

Player& Game::currentPlayerRef() {
	return players[currentPlayer];
}