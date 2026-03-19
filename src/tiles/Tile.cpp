#include "tiles/Tile.h"

Tile::Tile(const std::vector<Segment>& seg, const std::array<int, 9>& pos)
	: segments(seg), posToSegment(pos) {}

std::vector<Segment>& Tile::getSegments() {
	return segments;
}

const std::vector<Segment>& Tile::getSegments() const {
	return segments;
}

Segment& Tile::getSegment(int index) {
	return segments[index];
}

const Segment& Tile::getSegment(int index) const {
	return segments[index];
}

int Tile::getSegmentIndex(Direction dir) const {
	switch (dir) {
		case Direction::North: return posToSegment[static_cast<int>(TilePosition::N)];
		case Direction::East: return posToSegment[static_cast<int>(TilePosition::E)];
		case Direction::South: return posToSegment[static_cast<int>(TilePosition::S)];
		case Direction::West: return posToSegment[static_cast<int>(TilePosition::W)];
		default: throw std::invalid_argument("Unknown directions");
	}
}

int Tile::getSegmentIndex(TilePosition pos) const {
	return posToSegment[static_cast<int>(pos)];
}

void Tile::rotate(){
	std::array<int, 9> rotated;

	rotated[static_cast<int>(TilePosition::C)] = posToSegment[static_cast<int>(TilePosition::C)];
	rotated[static_cast<int>(TilePosition::E)] = posToSegment[static_cast<int>(TilePosition::N)];
	rotated[static_cast<int>(TilePosition::S)] = posToSegment[static_cast<int>(TilePosition::E)];
	rotated[static_cast<int>(TilePosition::W)] = posToSegment[static_cast<int>(TilePosition::S)];
	rotated[static_cast<int>(TilePosition::N)] = posToSegment[static_cast<int>(TilePosition::W)];

	rotated[static_cast<int>(TilePosition::NW)] = posToSegment[static_cast<int>(TilePosition::SW)];
	rotated[static_cast<int>(TilePosition::NE)] = posToSegment[static_cast<int>(TilePosition::NW)];
	rotated[static_cast<int>(TilePosition::SW)] = posToSegment[static_cast<int>(TilePosition::SE)];
	rotated[static_cast<int>(TilePosition::SE)] = posToSegment[static_cast<int>(TilePosition::NE)];

	posToSegment = rotated;
}