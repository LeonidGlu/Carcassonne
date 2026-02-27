#pragma once
#include "TileType.h"
#include <vector>

struct Segment {
	int id = -1;
	TileType type;
	std::vector<int> edges; //NESW
	std::vector<int> connections;

	bool hasMeeple = false;
	int ownerID = -1;
};
