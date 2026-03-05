#pragma once
#include "TileType.h"
#include <vector>

struct Segment {
	int id = -1;
	TileType type;
	std::vector<int> connections;

	Segment(TileType t) : type(t) {}
};
