#include "core/RegionManager.h"

TypedRegion& RegionManager::getRegion(TileType type) {
	if (type == TileType::City) return cityRegion;
	else if (type == TileType::Road) return roadRegion;
	else if (type == TileType::Field) return fieldRegion;
}

const TypedRegion& RegionManager::getRegion(TileType type) const {
	if (type == TileType::City) return cityRegion;
	else if (type == TileType::Road) return roadRegion;
	else if (type == TileType::Field) return fieldRegion;
}

void RegionManager::onTilePlaced(Tile& tile, Position pos, const Board& board) {
	initializeSegments(tile);
	connectSegments(tile);
	connectWithNeighbors(tile, pos, board);
	updateRegionInfo(tile, pos, board);
}

void RegionManager::initializeSegments(Tile& tile) {
	for (Segment& i : tile.getSegments()) {
		if (i.type == TileType::Monastery) {
			continue;
		}
		i.id = getRegion(i.type).addElement();
	}
}

void RegionManager::connectSegments(Tile& tile) {
	auto& seg = tile.getSegments();

	for (size_t i = 0; i < seg.size(); ++i) {
		if (seg[i].type == TileType::Monastery) {
			continue;
		}
		for (int connectionsIndex : seg[i].connections) {
			if (seg[i].type != seg[connectionsIndex].type) {
				continue;
			}
			getRegion(seg[i].type).unite(seg[i].id, seg[connectionsIndex].id);
		}
	}

}

void RegionManager::connectWithNeighbors(Tile& tile, Position pos, const Board& board) {
	const std::array<Position, 4> deltas = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} };
	
	for (int d = 0; d < 4; ++d) {
		Direction dir = static_cast<Direction>(d);
		Position neighborPos{ pos.x + deltas[d].x, pos.y + deltas[d].y };

		if (!board.hasTile(neighborPos)) {
			continue;
		}

		const Tile& neighbor = board.getTile(neighborPos);
		int segIndex = tile.getSegmentIndex(dir);
		int neighborSegIndex = tile.getSegmentIndex(opposite(dir));

		Segment& segment = tile.getSegment(segIndex);
		const Segment neighborSegment = tile.getSegment(neighborSegIndex);

		if (segment.type != neighborSegment.type) {
			continue;
		}
		if (segment.type == TileType::Monastery) {
			continue;
		}
		getRegion(segment.type).unite(segment.id, neighborSegment.id);
	}
}

void RegionManager::updateRegionInfo(Tile& tile, Position pos, const Board& board) {
	const std::array<Position, 4> deltas = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} };

	std::set<std::pair<TileType, int>> visitedComponents;

	for (int d = 0; d < 4; ++d) {
		Direction dir = static_cast<Direction>(d);
		Position neighborPos{ pos.x + deltas[d].x, pos.y + deltas[d].y };

		int segIndex = tile.getSegmentIndex(dir);
		const Segment& seg = tile.getSegment(segIndex);

		if (seg.type == TileType::Field) {
			continue;
		}
		if (seg.type == TileType::Monastery) {
			continue;
		}

		TypedRegion& region = getRegion(seg.type);
		if (!board.hasTile(neighborPos)) {
			region.addOpenEdges(seg.id);
		}
		else {
			const Tile& neighbor = board.getTile(neighborPos);
			int neighborSegIndex = neighbor.getSegmentIndex(opposite(dir));
			const Segment& neighborSeg = neighbor.getSegment(neighborSegIndex);
			region.removeOpenEdges(neighborSeg.id);
		}

		int root = region.getRoot(seg.id);
		auto key = std::make_pair(seg.type, root);

		if (!visitedComponents.count(key)) {
			region.incrementTileCount(seg.id);
			visitedComponents.insert(key);
		}
	}
}

bool RegionManager::isMonasteryClosed(Position pos, const Board& board) const {
	return true;
}