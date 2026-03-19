#pragma once
#include "common/Direction.h"
#include <stdexcept>

enum class TilePosition {
	NW = 0, N = 1, NE = 2,
	W = 3, C = 4, E = 5,
	SW = 6, S = 7, SE = 8
};

inline TilePosition directionToPosition(Direction dir) {
	switch (dir) {
		case Direction::North: return TilePosition::N;
		case Direction::East: return TilePosition::E;
		case Direction::South: return TilePosition::S;
		case Direction::West: return TilePosition::W;
		default: throw std::invalid_argument("Unknown directions");
	}
}