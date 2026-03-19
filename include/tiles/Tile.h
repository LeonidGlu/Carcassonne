#pragma once
#include <vector>
#include <array>
#include "common/Segments.h"
#include "common/Direction.h"
#include "TilePosition.h"

class Tile {
public:
	Tile(const std::vector<Segment>& seg, const std::array<int, 9>& pos);

	std::vector<Segment>& getSegments();
	const std::vector<Segment>& getSegments() const;

	Segment& getSegment(int index);
	const Segment& getSegment(int index) const;

	int getSegmentIndex(Direction dir) const;
	int getSegmentIndex(TilePosition pos) const;

	void rotate();

private:
	std::vector<Segment> segments;

	std::array<int, 9> posToSegment;
};