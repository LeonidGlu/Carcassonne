#pragma once
#include <map>
#include "Tile.h"
#include "Position.h"
#include "graph/Graph.h"
#include "graph/UnionFind.h"

class Board {
public:
	bool canPlaceTile(const Tile& tile, Position pos) const;
	bool placeTile(Tile tile, Position pos);

	bool isCityClosed(int segmentID) const;
	bool isRoadClosed(int segmentID) const;
	//bool isMonasteryClosed(int segmentID) const;

	int getCitySize(int segmentID) const;
	int getRoadSize(int segmentID) const;

	std::vector<Position> getValidPositions(const Tile& tile) const;

	const std::map<Position, Tile>& getTiles() const;

	UnionFind& getCityUF();
	UnionFind& getRoadUF();

private:
	std::map<Position, Tile> tiles;
	std::unordered_map<int, int> cityOpenEdges;
	std::unordered_map<int, int> roadOpenEdges;

	UnionFind cityUF;
	UnionFind roadUF;
	UnionFind fielUF;

	Graph cityGraph;
	Graph roadGraph;
	Graph fielGraph;
	
	void initializeSegments(Tile& tile);
	void connectSegments(Tile& tile);
	void connectWithNeighbors(Tile& tile, Position pos);
	void updateOpenEdges(Position pos);
};