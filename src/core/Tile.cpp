#include "core/Tile.h"

std::vector<Segment>& Tile::getSegments() {
	return segments;
}

const std::vector<Segment>& Tile::getSegments() const {
	return segments;
}

//Tile Tile::rotate() const{
//
//}