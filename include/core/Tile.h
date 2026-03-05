#pragma once
#include <vector>
#include <array>
#include "Segments.h"
#include "Direction.h"

class Tile {
public:
	Tile(const std::vector<Segment>& seg, const std::array<int, 4> edge) : segments(seg), edgeToSegment(edge) {}

	std::vector<Segment>& getSegments();
	const std::vector<Segment>& getSegments() const;

	Segment& getSegment(int index);
	const Segment& getSegment(int index) const;

	int getSegmentIndex(Direction dir) const;

	void rotate();
private:
	std::vector<Segment> segments;

	std::array<int, 4> edgeToSegment;
};