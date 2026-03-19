#pragma once
#include "tiles/TileFactory.h"
#include <vector>
#include <string>
#include <random>

class Deck {
public:
	Deck();
		
	Tile draw();
	bool isEmpty() const;
	int remaining() const;

private:
	std::vector<Tile> tiles;
	int currentIndex = 0;

	void shuffle();
};