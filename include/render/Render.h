#pragma once
#include "core/Board.h"
#include "tiles/Tile.h"
#include "game/Player.h"
#include "meeple/Meeple.h"
#include "core/MoveGenerator.h"
#include "common/TerminalColor.h"
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <map>

class Render {
public:
	void clearScreen() const;

	void renderBoard(const Board& board) const;
	void renderBoardWithMoves(const Board& board,const std::vector<Move>& moves) const;
	void renderTile(const Tile& tile) const;
	void renderScores(const std::vector<Player>& players) const;
	void renderValidMoves(const std::vector<Move>& moves) const;
	void renderMeepleInfo(TileType type, Position pos, const std::vector<Meeple>& meeples, const std::vector<Player>& players) const;

private:
	char getSymbol(TileType type) const;

	void getBoardBorder(const Board& board, int& minX, int& minY, int& maxX, int& maxY) const;

	void printCellLine(const Tile&, int line) const;
	void printEmptyCellLine() const;
	void printMoveCellLine(int moveIndex, int line) const;
};