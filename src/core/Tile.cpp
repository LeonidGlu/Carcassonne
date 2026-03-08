#include "core/Tile.h"

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
	return edgeToSegment[static_cast<int>(dir)];
}

void Tile::rotate(){
	int temp = edgeToSegment[3];
	edgeToSegment[3] = edgeToSegment[2];
	edgeToSegment[2] = edgeToSegment[1];
	edgeToSegment[1] = edgeToSegment[0];
	edgeToSegment[0] = temp;
}