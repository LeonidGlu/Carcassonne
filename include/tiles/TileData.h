#pragma once
#include "TileType.h"
#include <vector>
#include <array>
#include <string>

struct TileData {
	std::string name;
	std::vector<TileType> segTypes;
	std::array<int, 9> posToSeg;
};

extern const std::vector<TileData> ALL_TILES;