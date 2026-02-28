#include "core/Board.h"

bool Board::canPlaceTile(const Tile& tile, Position pos) const {
	return true;
}


bool Board::placeTile(Tile tile, Position pos) {
	if (!canPlaceTile(tile, pos)) {
		return false;
	}

	initializeSegments(tile);
	connectSegments(tile);
	connectWithNeighbors(tile, pos);

	tiles[pos] = tile;

	return true;
}

void Board::initializeSegments(Tile& tile) {
	for (auto& i : tile.getSegments()) {
		if (i.type == TileType::City) {
			i.id = cityUF.addElement();
			cityGraph.addNode(i.id);
			continue;
		}
		else if (i.type == TileType::Road) {
			i.id = roadUF.addElement();
			roadGraph.addNode(i.id);
			continue;
		}
		else if (i.type == TileType::Field) {
			i.id = fielUF.addElement();
			fielGraph.addNode(i.id);
			continue;
		}
		else continue;
	}
}

void Board::connectSegments(Tile& tile) {
	auto& seg = tile.getSegments();

	for (size_t i = 0; i < seg.size(); ++i) {
		for (int neirIndex : seg[i].connections) {
			if (seg[i].type != seg[neirIndex].type) {
				continue;
			}

			if (seg[i].type == TileType::City) {
				cityUF.unit(seg[i].id, seg[neirIndex].id);
				cityGraph.addEdge(seg[i].id, seg[neirIndex].id);
				continue;
			}
			else if (seg[i].type == TileType::Road) {
				roadUF.unit(seg[i].id, seg[neirIndex].id);
				roadGraph.addEdge(seg[i].id, seg[neirIndex].id);
				continue;
			}
			else if (seg[i].type == TileType::Field) {
				fielUF.unit(seg[i].id, seg[neirIndex].id);
				fielGraph.addEdge(seg[i].id, seg[neirIndex].id);
				continue;
			}
			else continue;
		}
	}
}

void Board::connectWithNeighbors(Tile& tile, Position pos) {
	static const std::vector<Position> directions = {
		{0, 1},   
		{1, 0},   
		{0, -1},  
		{-1, 0}   
	};

	for (int dir = 0; dir < 4; ++dir) {
		Position neighborPos = { pos.x + directions[dir].x,
								 pos.y + directions[dir].y };

		if (!tiles.count(neighborPos))
			continue;

		Tile& neighborTile = tiles[neighborPos];

		for (auto& seg : tile.getSegments()) {
			for (int edge : seg.edges) {
				if (edge != dir)
					continue;

				for (auto& neighborSeg : neighborTile.getSegments()) {
					for (int neighborEdge : neighborSeg.edges) {
						if (neighborEdge != (dir + 2) % 4)
							continue;

						if (seg.type != neighborSeg.type)
							continue;

						switch (seg.type) {
						case TileType::City:
							cityUF.unit(seg.id, neighborSeg.id);
							cityGraph.addEdge(seg.id, neighborSeg.id);
							break;

						case TileType::Road:
							roadUF.unit(seg.id, neighborSeg.id);
							roadGraph.addEdge(seg.id, neighborSeg.id);
							break;

						case TileType::Field:
							fielUF.unit(seg.id, neighborSeg.id);
							fielGraph.addEdge(seg.id, neighborSeg.id);
							break;

						default:
							break;
						}
					}
				}
			}
		}
	}
}