#pragma once
#include "meeple/MeepleType.h"

class Meeple {
public:
	Meeple() = default;

	Meeple(int playerIndex, MeepleType type);

	int getPlayer() const;
	MeepleType getMeepleType() const;

	void debug() const;

private:
	int playerIndex;
	MeepleType type;

};