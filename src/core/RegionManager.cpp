#include "core/RegionManager.h"
#include <iostream>

TypedRegion& RegionManager::getRegion(TileType type) {
	if (type == TileType::City) return cityRegion;
	else if (type == TileType::Road) return roadRegion;
	else if (type == TileType::Field) return fieldRegion;
	else throw std::invalid_argument("Unknown TileType");
}

const TypedRegion& RegionManager::getRegion(TileType type) const {
	if (type == TileType::City) return cityRegion;
	else if (type == TileType::Road) return roadRegion;
	else if (type == TileType::Field) return fieldRegion;
	else throw std::invalid_argument("Unknown TileType");
}

void RegionManager::onTilePlaced(Tile& tile, Position pos, const Board& board) {
	initializeSegments(tile);
	connectWithNeighbors(tile, pos, board);
	connectFieldCorners(tile, pos, board);
	updateRegionInfo(tile, pos, board);
	updateRegionGraph(tile);
}

const Graph& RegionManager::getRegionGraph() const {
	return regionGraph;
}

int RegionManager::encodedRegion(TileType type, int root) {
	return static_cast<int>(type) * 10000 + root;
}

std::pair<TileType, int> RegionManager::decodedRegion(int encoded) {
	TileType type = static_cast<TileType>(encoded / 10000);
	int root = encoded % 10000;
	return { type, root };
}

void RegionManager::mergeRegionGraphNodes(TileType type, int oldRootA, int oldRootB, int newRoot) {
	int encodeA = encodedRegion(type, oldRootA);
	int encodeB = encodedRegion(type, oldRootB);
	int encodeNew = encodedRegion(type, newRoot);

	std::set<int> allNeighbors;

	for (int neighbor : regionGraph.getNeighbors(encodeA)) {
		if (neighbor != encodeB) {
			allNeighbors.insert(neighbor);
		}
	}

	for (int neighbor : regionGraph.getNeighbors(encodeB)) {
		if (neighbor != encodeA) {
			allNeighbors.insert(neighbor);
		}
	}

	regionGraph.removeNode(encodeA);
	regionGraph.removeNode(encodeB);

	regionGraph.addNode(encodeNew);
	for (int neighbor : allNeighbors) {
		regionGraph.addEdge(encodeNew, neighbor);
	}
}

void RegionManager::updateRegionGraph(Tile& tile) {
	static const std::map<TilePosition, std::vector<TilePosition>> adjacentPositions = {
		{ TilePosition::NW, { TilePosition::N,  TilePosition::W,  TilePosition::C } },
		{ TilePosition::N,  { TilePosition::NW, TilePosition::NE, TilePosition::C } },
		{ TilePosition::NE, { TilePosition::N,  TilePosition::E,  TilePosition::C } },
		{ TilePosition::W,  { TilePosition::NW, TilePosition::SW, TilePosition::C } },
		{ TilePosition::C,  { TilePosition::NW, TilePosition::N,  TilePosition::NE,
							  TilePosition::W,  TilePosition::E,
							  TilePosition::SW, TilePosition::S,  TilePosition::SE } },
		{ TilePosition::E,  { TilePosition::NE, TilePosition::SE, TilePosition::C } },
		{ TilePosition::SW, { TilePosition::W,  TilePosition::S,  TilePosition::C } },
		{ TilePosition::S,  { TilePosition::SW, TilePosition::SE, TilePosition::C } },
		{ TilePosition::SE, { TilePosition::E,  TilePosition::S,  TilePosition::C } }
	};

	// Добавляем узлы для всех регионов нового тайла
	for (const Segment& seg : tile.getSegments()) {
		if (seg.id < 0) continue;
		if (seg.type == TileType::Crossroad) continue;
		if (seg.type == TileType::Monastery) continue;

		int root = getRegion(seg.type).getRoot(seg.id);
		regionGraph.addNode(encodedRegion(seg.type, root));
	}

	// Добавляем рёбра между реально соседними сегментами разных типов
	for (auto& neighbors : adjacentPositions) {
		int segIdxA = tile.getSegmentIndex(neighbors.first);
		const Segment& segA = tile.getSegment(segIdxA);

		if (segA.id < 0) continue;
		if (segA.type == TileType::Crossroad) continue;
		if (segA.type == TileType::Monastery) continue;

		for (TilePosition neighborPos : neighbors.second) {
			int segIdxB = tile.getSegmentIndex(neighborPos);
			const Segment& segB = tile.getSegment(segIdxB);

			if (segB.id < 0) continue;
			if (segB.type == TileType::Crossroad) continue;
			if (segB.type == TileType::Monastery) continue;
			if (segA.type == segB.type) continue;

			int rootA = getRegion(segA.type).getRoot(segA.id);
			int rootB = getRegion(segB.type).getRoot(segB.id);

			regionGraph.addEdge(
				encodedRegion(segA.type, rootA),
				encodedRegion(segB.type, rootB)
			);
		}
	}
}

void RegionManager::initializeSegments(Tile& tile) {
	for (Segment& i : tile.getSegments()) {
		if (i.type == TileType::Monastery) {
			continue;
		}
		if (i.type == TileType::Crossroad) {
			continue;
		}
		i.id = getRegion(i.type).addElement();
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
		int neighborSegIndex = neighbor.getSegmentIndex(opposite(dir));

		Segment& segment = tile.getSegment(segIndex);
		const Segment neighborSegment = neighbor.getSegment(neighborSegIndex);

		if (segment.type == TileType::Field) {
			continue;
		}
		if (segment.type == TileType::Monastery) {
			continue;
		}
		if (segment.type == TileType::Crossroad) {
			continue;
		}
		if (neighborSegment.type == TileType::Crossroad) {
			continue;
		}
		if (segment.type != neighborSegment.type) {
			continue;
		}
		 
		UniteResult result = getRegion(segment.type).unite(segment.id, neighborSegment.id);

		if (result.merged) {

		}
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
		if (seg.type == TileType::Crossroad) {
			if (board.hasTile(neighborPos)) {
				const Tile& neighbor = board.getTile(neighborPos);
				int neighborSegIndex = neighbor.getSegmentIndex(opposite(dir));
				const Segment& neighborSeg = neighbor.getSegment(neighborSegIndex);

				if (neighborSeg.type == TileType::Road) {
					roadRegion.removeOpenEdges(neighborSeg.id);
				}
			}
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

			if (!(neighborSeg.type == TileType::Crossroad)) {
				region.removeOpenEdges(neighborSeg.id);
			}
		}

		int root = region.getRoot(seg.id);
		auto key = std::make_pair(seg.type, root);

		if (!visitedComponents.count(key)) {
			region.incrementTileCount(seg.id);
			visitedComponents.insert(key);
		}
	}
}

void RegionManager::connectFieldCorners(Tile& tile, Position pos, const Board& board) {
	const std::array<Position, 4> deltas = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} };

	const std::array<std::array<std::pair<TilePosition, TilePosition>, 2>, 4> corners = { {
		{{{TilePosition::NW, TilePosition::SW}, {TilePosition::NE, TilePosition::SE}}},
		{{{TilePosition::NE, TilePosition::NW}, {TilePosition::SE, TilePosition::SW}}},
		{{{TilePosition::SW, TilePosition::NW}, {TilePosition::SE, TilePosition::NE}}},
		{{{TilePosition::NW, TilePosition::NE}, {TilePosition::SW, TilePosition::SE}}}
	} };

	for (int d = 0; d < 4; ++d) {
		Position neighborPos{ pos.x + deltas[d].x, pos.y + deltas[d].y };

		if (!board.hasTile(neighborPos)) {
			continue;
		}

		const Tile& neighbor = board.getTile(neighborPos);
		for (auto& corner : corners[d]) {
			int segIndex = tile.getSegmentIndex(corner.first);
			int neighborSegIndex = neighbor.getSegmentIndex(corner.second);

			const Segment& seg = tile.getSegment(segIndex);
			const Segment& neighborSeg = neighbor.getSegment(neighborSegIndex);

			if (seg.type != TileType::Field) {
				continue;
			}
			if (neighborSeg.type != TileType::Field) {
				continue;
			}
			
			UniteResult result = fieldRegion.unite(seg.id, neighborSeg.id);

			if (result.merged) {
				mergeRegionGraphNodes(TileType::Field, result.oldRootA, result.oldRootB, result.newRoot);
			}
		}
	}
}

bool RegionManager::isMonasteryClosed(Position pos, const Board& board) const {
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0) {
				continue;
			}
			if (!board.hasTile({ pos.x + x, pos.y + y })) {
				return false;
			}
		}
	}
	return true;
}

void RegionManager::onMeeplePlaced(int segmentID, TileType type, Meeple meeple) {
	getRegion(type).addMeeple(segmentID, meeple);
}

void RegionManager::onMonasteryMeeplePlaced(Position pos, Meeple meeple) {
	monasteryMeeples[pos].push_back(meeple);
}

std::vector<Meeple> RegionManager::getMeeples(int segmentID, TileType type) const {
	return getRegion(type).getMeeples(segmentID);
}

std::vector<Meeple> RegionManager::getMonasteryMeeples(Position pos) const {
	auto it = monasteryMeeples.find(pos);
	if (it == monasteryMeeples.end()) {
		return {};
	}
	return it->second;
}

void RegionManager::clearMeeples(int segmentID, TileType type) {
	getRegion(type).clearMeeples(segmentID);
}

void RegionManager::clearMonasteryMeeples(Position pos) {
	monasteryMeeples.erase(pos);
}

void RegionManager::debug() const {
	std::cout << "\n========== RegionManager ==========\n";
	cityRegion.debug("City");
	roadRegion.debug("Road");
	fieldRegion.debug("Field");

	debugRegionGraph();

	if (!monasteryMeeples.empty()) {
		std::cout << "  --- Monastery meeples ---\n";
		for (auto& i : monasteryMeeples) {
			std::cout << "    pos=(" << i.first.x << "," << i.first.y << ") | meeples: [";
			for (size_t j = 0; j < i.second.size(); ++j) {
				if (j > 0) std::cout << ", ";
				std::cout << "p" << i.second[j].getPlayer();
			}
			std::cout << "]\n";
		}
	}
	std::cout << "====================================\n";
}

void RegionManager::debugFieldRegions(const Board& board) {
	std::cout << "\n========== FIELD REGIONS PER TILE ==========\n";
	
	for (const auto& tile : board.getAllTiles()) {
		std::cout << "Tile (" << tile.first.x << ", " << tile.first.y << "):\n";

		std::set<int> visitedSegments;

		for (const Segment& seg : tile.second.getSegments()) {
			if (seg.type != TileType::Field) {
				continue;
			}
			if (seg.id < 0) {
				continue;
			}
			if (visitedSegments.count(seg.id)) {
				continue;
			}

			visitedSegments.insert(seg.id);
			int root = fieldRegion.getRoot(seg.id);
			std::cout << " segmentID= " << seg.id << " ---> root= " << root << "\n";
		}

	}
}

void RegionManager::debugRegionGraph() const {
	std::cout << "\n========== Region Graph ==========\n";

	if (regionGraph.isEmpty()) {
		std::cout << "(empty)\n";
		std::cout << "=====================================\n";
		return;
	}

	for (auto& encoded : regionGraph.getAdjacencyGraph()) {
		auto a = decodedRegion(encoded.first);
		std::cout << a.first << "(root = " << a.second << ") ---> [";

		bool first = true;
		for (int neighbor : encoded.second) {
			auto neighborDecoded = decodedRegion(neighbor);
			if (!first) {
				std::cout << ", ";
			}
			std::cout << neighborDecoded.first << "(root = " << neighborDecoded.second << ")";
			first = false;
		}
		std::cout << "\n";
	}
	std::cout << "=====================================\n";
}
