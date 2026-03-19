#include "game/Deck.h"

static const std::vector<std::pair<std::string, int>> DECK = {
    { "StartTile",    1 },
    { "StraightRoad", 8 },
    { "CurvedRoad",   9 },
    { "Monastery",    4 },
    { "CityOne",      5 },
    { "CityTwo",      3 },
    { "CityCorner",   3 },
    { "FullCity",     1 },
};

Deck::Deck() {
    for (auto& tile : DECK) {
        for (int i = 0; i < tile.second; ++i) {
            tiles.push_back(TileFactory::create(tile.first));
        }
    }
    shuffle();
}

Tile Deck::draw() {
    if (isEmpty()) {
        throw std::runtime_error("Deck is empty!");
    }
    return tiles[currentIndex++];
}

bool Deck::isEmpty() const {
    return currentIndex >= static_cast<int>(tiles.size());
}

int Deck::remaining() const {
    return static_cast<int>(tiles.size()) - currentIndex;
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(tiles.begin(), tiles.end(), rng);
}