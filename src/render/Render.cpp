#include "render/Render.h"

char Render::getSymbol(TileType type) const {
	switch(type) {
		case TileType::City: return 'C';
		case TileType::Field: return 'F';
		case TileType::Monastery: return 'M';
		case TileType::Road: return 'R';
		case TileType::Crossroad: return 'X';
		default: return '?';
	}
}

void Render::clearScreen() const {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif 
}

void Render::getBoardBorder(const Board& board, int& minX, int& minY, int& maxX, int& maxY) const {
	minX = minY = 999;
	maxX = maxY = -999;

	for (auto& tile : board.getAllTiles()) {
		minX = std::min(minX, tile.first.x);
		minY = std::min(minY, tile.first.y);
		maxX = std::max(maxX, tile.first.x);
		maxY = std::max(maxY, tile.first.y);
	}
}

void Render::printCellLine(const Tile& tile, int line)  const {
	static const std::array<std::array<TilePosition, 3>, 3> pos = { {
		{{ TilePosition::NW, TilePosition::N,  TilePosition::NE }},
		{{ TilePosition::W,  TilePosition::C,  TilePosition::E  }},
		{{ TilePosition::SW, TilePosition::S,  TilePosition::SE }}
	} };

	std::cout << "[";
	for (int i = 0; i < 3; ++i) {
		int segIndex = tile.getSegmentIndex(pos[line][i]);
		const Segment& seg = tile.getSegment(segIndex);
		std::cout << TerminalColor::getSegmentColor(seg) << getSymbol(seg.type) << TerminalColor::RESET;
	}
	std::cout << "]";
}

void Render::printEmptyCellLine() const {
	std::cout << " ... ";
}

void Render::printMoveCellLine(int moveIndex, int line) const {
	if (line == 1) {
		if (moveIndex < 10) {
			std::cout << "[^" << moveIndex << "^]";
		}
		else {
			std::cout << "[^" << moveIndex << "]";
		}
	}
	else {
		std::cout << "[^^^]";
	}
}

void Render::renderBoard(const Board& board) const {
	if (board.isEmpty()) {
		std::cout << "[Board is empty!]\n";
		return;
	}

	int minX, minY, maxX, maxY;
	getBoardBorder(board, minX, minY, maxX, maxY);

	std::cout << "------BOARD------\n\n";

	std::cout << "     ";
	for (int x = minX; x <= maxX; ++x) {
		std::cout << std::setw(5) << x;
	}
	std::cout << "\n";

	for (int y = maxY; y >= minY; --y) {
		for (int line = 0; line < 3; ++line) {
			if (line == 1) {
				std::cout << std::setw(4) << y << " ";
			}
			else {
				std::cout << "     ";
			}

			for (int x = minX; x <= maxX; ++x) {
				if (board.hasTile({ x, y })) {
					const Tile& tile = board.getTile({ x, y });
					printCellLine(tile, line);
				}
				else {
					printEmptyCellLine();
				}
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
}

void Render::renderBoardWithMoves(const Board& board, const std::vector<Move>& moves) const {
	if (board.isEmpty()) {
		std::cout << "[Board is empty!]\n";
		return;
	}

	std::map<std::pair<int, int>, int> moveMap;
	for (size_t i = 0; i < moves.size(); ++i) {
		moveMap[{moves[i].pos.x, moves[i].pos.y}] = static_cast<int>(i);
	}

	int minX, minY, maxX, maxY;
	getBoardBorder(board, minX, minY, maxX, maxY);

	for (const auto& move : moves) {
		minX = std::min(minX, move.pos.x);
		minY = std::min(minY, move.pos.y);
		maxX = std::max(maxX, move.pos.x);
		maxY = std::max(maxY, move.pos.y);
	}

	std::cout << "------BOARD------\n\n";

	std::cout << "     ";
	for (int x = minX; x <= maxX; ++x) {
		std::cout << std::setw(5) << x;
	}
	std::cout << "\n";

	for (int y = maxY; y >= minY; --y) {
		for (int line = 0; line < 3; ++line) {
			if (line == 1) {
				std::cout << std::setw(4) << y << " ";
			}
			else {
				std::cout << "     ";
			}

			for (int x = minX; x <= maxX; ++x) {
				auto key = std::make_pair(x, y);

				if (board.hasTile({ x, y })) {
					printCellLine(board.getTile({ x, y }), line);
				}
				else if (moveMap.count(key)) {
					printMoveCellLine(moveMap[key], line);
				}
				else {
					printEmptyCellLine();
				}
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	renderValidMoves(moves);
}

void Render::renderTile(const Tile& tile) const {
	std::cout << "\n--- CURRENT TILE ---\n";

	for (int row = 0; row < 3; ++row) {
		printCellLine(tile, row);
		std::cout << "\n";
	}
}

void Render::renderScores(const std::vector<Player>& players) const {
	std::cout << "\n--- CURRENT SCORE ---\n";

	for (const auto& player : players) {
		std::cout << player.getName() << ": " << player.getScore() << " scores\n";
	}
}

void Render::renderValidMoves(const std::vector<Move>& moves) const {
	std::cout << "\n--- AVAILABLE MOVES ---\n";

	for (size_t i = 0; i < moves.size(); ++i) {
		std::cout << "[" << std::setw(2) << i << "]" << " -> ("
			<< std::setw(2) << moves[i].pos.x << ", "
			<< std::setw(2) << moves[i].pos.y << ")\n";
	}
}

void Render::renderMeepleInfo(TileType type, Position pos, const std::vector<Meeple>& meeples, const std::vector<Player>& players) const {
	std::unordered_map<int, int> count;
	for (const Meeple& meeple : meeples) {
		count[meeple.getPlayer()]++;
	}

	std::cout << type << " (" << pos.x << ", " << pos.y << "): ";
	
	if (count.size() == 1) {
		auto& meepleCnt = *count.begin();
		std::cout << players[meepleCnt.first].getName();
		if (meepleCnt.second > 1) std::cout << "(" << meepleCnt.second << ")";
	}
	else {
		std::cout << "[CONTESTED] ";
		bool first = true;
		for (auto& meepleCnt : count) {
			if (!first) {
				std::cout << " vs ";
			}
			std::cout << players[meepleCnt.first].getName() << "(" << meepleCnt.second << ")";
			first = false;
		}
	}

	std::cout << "\n";
}