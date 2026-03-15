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