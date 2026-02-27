#pragma once

struct Position {
	int x;
	int y;

	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}

	bool operator<(const Position& other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	}

	bool operator>(const Position& other) const {
		return std::tie(x, y) > std::tie(other.x, other.y);
	}
};