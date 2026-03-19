#pragma once

enum class Direction {
	North = 0,
	East = 1,
	South = 2,
	West = 3
};

inline Direction opposite(Direction dir) {
	return static_cast<Direction>((static_cast<int>(dir) + 2) % 4);
}