#pragma once
#include "Tile.h"
#include "TileData.h"
#include <string>

class TileFactory {
public:
	static Tile create(const std::string& name);

private:
	static Tile createTile(const TileData& data);
	static const TileData& findData(const std::string& name);
};