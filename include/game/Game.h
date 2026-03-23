#pragma once
#include "core/GameState.h"
#include "game/Deck.h"
#include "game/Player.h"
#include "render/Render.h"
#include "core/MoveGenerator.h"
#include "tiles/TileFactory.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>


class Game {
public:
	explicit Game(int playerCount);

	void run();

private:
	GameState gameState;
	Deck deck;
	std::vector<Player> players;
	Render render;
	int currentPlayer = 0;

	void placeStartTile();

	void playTurn();
	void nextPlayer();
	void endGame();

	Move getPlayerMove(const Tile& tile);
	int askRotation() const;
	Move askPosition(const std::vector<Move>& moves) const;

	Player& currentPlayerRef();

};