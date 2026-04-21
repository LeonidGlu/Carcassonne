#include "meeple/Meeple.h"

Meeple::Meeple(int playerIndex, MeepleType type) : playerIndex(playerIndex), type(type) {}

int Meeple::getPlayer() const {
	return playerIndex;
}

MeepleType Meeple::getMeepleType() const {
	return type;
}

void Meeple::debug() const {
	std::cout << "Meeple [player = " << playerIndex << ", type = " << type << "]\n";
}