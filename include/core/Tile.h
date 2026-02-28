#pragma once
#include <vector>
#include "Segments.h"

class Tile {
public:
	Tile() = default;

	std::vector<Segment>& getSegments();
	const std::vector<Segment>& getSegments() const;

	void rotate();
private:
	std::vector<Segment> segments;
};