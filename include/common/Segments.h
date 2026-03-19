#pragma once
#include "tiles/TileType.h"
#include <vector>

struct Segment {
	int id = -1;
	TileType type;

	Segment(TileType t) : type(t) {}
};
