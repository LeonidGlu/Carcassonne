#include "core/TypedRegion.h"

int TypedRegion::addElement() {
	int id = uf.addElement();
	graph.addNode(id);
	regions[id] = RegionInfo{};
	return id;
}

void TypedRegion::unite(int idA, int idB) {
	int rootA = uf.find(idA);
	int rootB = uf.find(idB);

	if (rootA == rootB) {
		graph.addEdge(idA, idB);
		return;
	}

	RegionInfo merged;
	merged.openEdges = regions[rootA].openEdges + regions[rootB].openEdges;
	merged.tileCount = regions[rootA].tileCount + regions[rootB].tileCount;

	uf.unit(idA, idB);
	graph.addEdge(idA, idB);

	int newRoot = uf.find(idA);

	regions[newRoot] = merged;

	if (newRoot != rootA) {
		regions.erase(rootA);
	}
	if (newRoot != rootB) {
		regions.erase(rootB);
	}

	transferMeeples(rootA, newRoot);
	transferMeeples(rootB, newRoot);
}

bool TypedRegion::isClosed(int segmentID) const {
	int root = uf.find(segmentID);
	auto it = regions.find(root);
	if (it == regions.end()) {
		return false;
	}
	return it->second.openEdges == 0;
}

int TypedRegion::getTileCount(int segmentID) const {
	int root = uf.find(segmentID);
	auto it = regions.find(root);
	if (it == regions.end()) {
		return 0;
	}
	return it->second.tileCount;
}

int TypedRegion::getOpenEdges(int segmentID) const {
	int root = uf.find(segmentID);
	auto it = regions.find(root);
	if (it == regions.end()) {
		return 0;
	}
	return it->second.openEdges;
}

int TypedRegion::getRoot(int segmentID) const {
	return uf.find(segmentID);
}

void TypedRegion::addOpenEdges(int segmentID) {
	int root = uf.find(segmentID);
	auto it = regions.find(root);
	if (it == regions.end()) {
		return;
	}
	it->second.openEdges++;
}

void TypedRegion::removeOpenEdges(int segmentID) {
	int root = uf.find(segmentID);
	auto it = regions.find(root);
	if (it == regions.end()) {
		return;
	}
	if (it->second.openEdges > 0) {
		it->second.openEdges--;
	}
}

void TypedRegion::incrementTileCount(int segmentID) {
	int root = uf.find(segmentID);
	auto it = regions.find(root);
	if (it == regions.end()) {
		return;
	}
	it->second.tileCount++;
}

void TypedRegion::addMeeple(int segmentID, Meeple meeple) {
	int root = uf.find(segmentID);
	meeples[root].push_back(meeple);
}

std::vector<Meeple> TypedRegion::getMeeples(int segmentID) const {
	int root = uf.find(segmentID);
	auto it = meeples.find(root);
	if (it == meeples.end()) {
		return {};
	}
	return it->second;
}

void TypedRegion::clearMeeples(int segmentID) {
	int root = uf.find(segmentID);
	meeples.erase(root);
}

void TypedRegion::transferMeeples(int from, int to) {
	if (from == to) {
		return;
	}
	auto it = meeples.find(from);
	if (it == meeples.end()) {
		return;
	}

	auto& target = meeples[to];
	target.insert(target.end(), it->second.begin(), it->second.end());
	meeples.erase(it);
}

void TypedRegion::debug(const std::string& name) const {
	if (!name.empty()) {
		std::cout << "  --- " << name << " ---\n";
	}

	if (regions.empty()) {
		std::cout << "  (no regions)\n";
		return;
	}

	std::cout << "  Regions:\n";
	for (auto& i : regions) {
		std::cout << "    root=" << std::setw(3) << i.first
			<< " | openEdges=" << std::setw(2) << i.second.openEdges
			<< " | tileCount=" << std::setw(2) << i.second.tileCount
			<< (i.second.openEdges == 0 ? " [CLOSED]" : " [OPEN]");

		auto it = meeples.find(i.first);
		if (it != meeples.end() && !it->second.empty()) {
			std::cout << " | meeples: [";
			for (size_t j = 0; j < it->second.size(); ++j) {
				if (j > 0) std::cout << ", ";
				std::cout << "player" << it->second[j].getPlayer();
			}
			std::cout << "]";
		}
		else {
			std::cout << " | meeples: []";
		}

		std::cout << "\n";
	}

	uf.debug();

	std::cout << "  Graph:\n";
	graph.debug();
}