#include "tiles/TileFactory.h"

Tile TileFactory::create(const std::string& name) {
	return createTile(findData(name));
}

Tile TileFactory::createTile(const TileData& data) {
	std::vector<Segment> segments;
	segments.reserve(data.segTypes.size());

	for (TileType type : data.segTypes) {
		segments.emplace_back(type);
	}

	return Tile(segments, data.posToSeg);
}

const TileData& TileFactory::findData(const std::string& name) {
	for (const auto& data : ALL_TILES) {
		if (data.name == name) {
			return data;
		}
	}
	throw std::invalid_argument("Unknown tile: " + name);
}