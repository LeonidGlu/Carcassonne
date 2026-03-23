#pragma once
#include "core/Board.h"
#include "tiles/Tile.h"
#include "game/Player.h"
#include "core/MoveGenerator.h"
#include <iostream>
#include <iomanip>

class Render {
public:
	void clearScreen() const;

	void renderBoard(const Board& board) const;
	void renderBoardWithMoves(const Board& board, const std::vector<Move>& moves) const;
	void renderTile(const Tile& tile) const;
	void renderScores(const std::vector<Player>& players) const;
	void renderValidMoves(const std::vector<Move>& moves) const;

private:
	char getSymbol(TileType type) const;

	void getBoardBorder(const Board& board, int& minX, int& minY, int& maxX, int& maxY) const;

	void printCellLine(const Tile& tile, int line) const;
	void printEmptyCellLine() const;
	void printMoveCellLine(int moveIndex, int line) const;
};