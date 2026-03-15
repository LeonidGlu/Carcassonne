#include "core/Board.h"

const Tile& Board::getTile(Position pos) const {
	return tiles.at(pos);
}

Tile& Board::getTile(Position pos) {
	return tiles.at(pos);
}

const std::map<Position, Tile>& Board::getAllTiles() const {
	return tiles;
}

bool Board::hasTile(Position pos) const {
	return tiles.count(pos) > 0;
}

void Board::setTile(Position pos, Tile tile) {
	tiles[pos] = std::move(tile);
}

bool Board::isEmpty() const {
	return tiles.empty();
}

//#include "core/Board.h"
//
//const std::map<Position, Tile>& Board::getTiles() const {
//	return tiles;
//}
//
//UnionFind& Board::getCityUF() {
//	return cityUF;
//}
//
//UnionFind& Board::getRoadUF() {
//	return roadUF;
//}
//
//bool Board::isCityClosed(int segmentID) const {
//	int root = cityUF.find(segmentID);
//
//	auto it = cityOpenEdges.find(root);
//	if (it == cityOpenEdges.end()) {
//		return false;
//	}
//	return it->second == 0;
//}
//
//bool Board::isRoadClosed(int segmentID) const {
//	int root = roadUF.find(segmentID);
//
//	auto it = roadOpenEdges.find(root);
//	if (it == roadOpenEdges.end()) {
//		return false;
//	}
//	return it->second == 0;
//}
//
//bool Board::canPlaceTile(const Tile& tile, Position pos) const {
//	if (tiles.empty()) {
//		return true;
//	}
//
//	if (tiles.count(pos)) {
//		return false;
//	}
//
//	bool hasNeighbors = false;
//
//	static const std::array<Position, 4> directions = { {
//		{0, 1}, {1, 0}, {0, -1}, {-1, 0}
//	} };
//
//	for (int d = 0; d < 4; ++d) {
//		Direction dir = static_cast<Direction>(d);
//		Position neighborPos{ pos.x + directions[d].x, pos.y + directions[d].y };
//
//		if (!tiles.count(neighborPos)) {
//			continue;
//		}
//
//		hasNeighbors = true;
//
//		const Tile& neighborTile = tiles.at(neighborPos);
//
//		int segIndex = tile.getSegmentIndex(dir);
//		int neighborIndex = neighborTile.getSegmentIndex(opposite(dir));
//
//		if (tile.getSegment(segIndex).type != neighborTile.getSegment(neighborIndex).type) {
//			return false;
//		}
//	}
//
//	return hasNeighbors;
//}
//
//bool Board::placeTile(Tile tile, Position pos) {
//	if (!canPlaceTile(tile, pos)) {
//		return false;
//	}
//
//	initializeSegments(tile);
//	connectSegments(tile);
//	connectWithNeighbors(tile, pos);
//
//	tiles[pos] = tile;
//
//	updateOpenEdges(pos);
//
//	return true;
//}
//
//void Board::initializeSegments(Tile& tile) {
//	for (auto& i : tile.getSegments()) {
//		if (i.type == TileType::City) {
//			i.id = cityUF.addElement();
//			cityGraph.addNode(i.id);
//			continue;
//		}
//		else if (i.type == TileType::Road) {
//			i.id = roadUF.addElement();
//			roadGraph.addNode(i.id);
//			continue;
//		}
//		else if (i.type == TileType::Field) {
//			i.id = fielUF.addElement();
//			fielGraph.addNode(i.id);
//			continue;
//		}
//		else continue;
//	}
//}
//
//void Board::connectSegments(Tile& tile) {
//	auto& seg = tile.getSegments();
//
//	for (size_t i = 0; i < seg.size(); ++i) {
//		for (int neirIndex : seg[i].connections) {
//
//			if (seg[i].type != seg[neirIndex].type) {
//				continue;
//			}
//
//			if (seg[i].type == TileType::City) {
//				cityUF.unit(seg[i].id, seg[neirIndex].id);
//				cityGraph.addEdge(seg[i].id, seg[neirIndex].id);
//				continue;
//			}
//			else if (seg[i].type == TileType::Road) {
//				roadUF.unit(seg[i].id, seg[neirIndex].id);
//				roadGraph.addEdge(seg[i].id, seg[neirIndex].id);
//				continue;
//			}
//			else if (seg[i].type == TileType::Field) {
//				fielUF.unit(seg[i].id, seg[neirIndex].id);
//				fielGraph.addEdge(seg[i].id, seg[neirIndex].id);
//				continue;
//			}
//			else continue;
//		}
//	}
//}
//
//void Board::connectWithNeighbors(Tile& tile, Position pos) {
//	static const std::array<Position, 4> directions = { {
//		{0, 1}, {1, 0}, {0, -1}, {-1, 0}
//	} };
//
//	for (int d = 0; d < 4; ++d) {
//		Direction dir = static_cast<Direction>(d);
//		Position neighborPos{ pos.x + directions[d].x, pos.y + directions[d].y };
//
//		if (!tiles.count(neighborPos)) {
//			continue;
//		}
//
//		Tile& neighborTile = tiles[neighborPos];
//
//		int segIndex = tile.getSegmentIndex(dir);
//		int neighborIndex = neighborTile.getSegmentIndex(opposite(dir));
//
//		Segment& seg = tile.getSegment(segIndex);
//		Segment& neighborSeg = neighborTile.getSegment(neighborIndex);
//
//		if (seg.type == TileType::City) {
//			cityUF.unit(seg.id, neighborSeg.id);
//			cityGraph.addEdge(seg.id, neighborSeg.id);
//		}
//		else if (seg.type == TileType::Road) {
//			roadUF.unit(seg.id, neighborSeg.id);
//			roadGraph.addEdge(seg.id, neighborSeg.id);
//		}
//		else if (seg.type == TileType::Field) {
//			fielUF.unit(seg.id, neighborSeg.id);
//			fielGraph.addEdge(seg.id, neighborSeg.id);
//		}
//	}
//}
//
//void Board::updateOpenEdges(Position pos) {
//	const Tile& tile = tiles.at(pos);
//
//	static const std::array<Position, 4> directions = { {
//		{0, 1}, {1, 0}, {0, -1}, {-1, 0}
//	} };
//
//	for (int d = 0; d < 4; ++d) {
//		Direction dir = static_cast<Direction>(d);
//		Position neighborPos{ pos.x + directions[d].x, pos.y + directions[d].y };
//
//		int segIndex = tile.getSegmentIndex(dir);
//		const Segment& seg = tile.getSegment(segIndex);
//
//		if (seg.type != TileType::City && seg.type != TileType::Road) {
//			continue;
//		}
//
//		UnionFind& uf = (seg.type == TileType::City) ? cityUF : roadUF;
//		auto& openEdges = (seg.type == TileType::City) ? cityOpenEdges : roadOpenEdges;
//
//		int segRoot = uf.find(seg.id);
//
//		if (!tiles.count(neighborPos)) {
//			openEdges[segRoot]++;
//		}
//		else {
//			const Tile& neighborTile = tiles.at(neighborPos);
//			int neighborSegIndex = neighborTile.getSegmentIndex(opposite(dir));
//			const Segment& neighborSeg = neighborTile.getSegment(neighborSegIndex);
//
//			int neighborSegRoot = uf.find(neighborSeg.id);
//
//			if (openEdges.count(neighborSegRoot) && openEdges[neighborSegRoot] > 0) {
//				openEdges[neighborSegRoot]--;
//			}
//		}
//	}
//}